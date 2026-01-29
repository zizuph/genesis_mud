/*
* Created by: Luther
* Date: Jan 2002
*
* File: /d/Cirath/tyr/jail/zarth_reaper.c
* Comments: The psionict foe who helps Zarth when he is in trouble
*           
*/

#pragma strict_types
#pragma save_binary
 
inherit "/d/Cirath/std/monster.c";
inherit "/d/Kalad/lib/special.c";

#include "/d/Cirath/common/defs.h"
#include "/sys/stdproperties.h"
#include <filter_funs.h>
#include "defs.h"
#include <wa_types.h>
#include <macros.h>
#include <options.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <formulas.h>
#include <composite.h>
#include <options.h>
#include <std.h>
#include <filter_funs.h>
#include <cmdparse.h>

int r;

void
zarth_help();

void
create_monster ()
{
	set_name("witlok");
	set_title("Bloodreaver of the Black Waste");
	set_race_name("human");
	set_adj("keen");

	set_long("Tall and lean, this sunken-cheeked bald human still manages to " +
		"look commanding. His every movement reeks of power, and you " + 
		"can almost feel it radiating from his body. His taught, sallow " + 
		"skin makes him look sickly and weak, but the grace with which " +
		"he moves and the glint in his eye makes you think otherwise. " +
		"Deep black tattoos cover his head, seemingly writhing with life " +
		"in the bright Athasian sun.\n");

	set_stats(({ 100, 140, 140, 200, 180, 160}));

	set_skill(SS_DEFENCE, 40);
	set_skill(SS_PARRY, 30);
	set_skill(SS_UNARM_COMBAT, 100);
	set_skill(SS_AWARENESS, 90);	
	add_prop(NPC_I_NO_RUN_AWAY, 1);
	add_prop(LIVE_I_SEE_DARK, 10);
	add_prop (LIVE_I_NEVERKNOWN, 1);
	set_alignment(0);
	r = 0;	
}

void
arm_me()
{
	object claw;    	
    	claw = clone_object(TYR_WEP + "reaper_claw");
	claw->right();
	claw->move(TO);
	clone_object(TYR_ARM + "reaper_cloak.c")->move(TO);
	command("wear all");
}

void
zarth_help()
{
	command("assist zarth");
}

/* sets unarmed combat off, giving more attacks! */
int
query_option(int opt)
{
  return (opt == OPT_UNARMED_OFF);
}

void
attacked_by(object ob)
{
	::attacked_by(ob);	
	environment(this_object())-> jalla_func4(ob);	
}
/*
varargs public mixed
hit_me(int wcpen, int dt, object attacker, int attack_id, int target_hitloc=-1)
{
	if ((query_hp()< 1600) && (!r))
	{
		r = 1;		
		if ((!can_see_in_room()) && TP->query_weapon(W_LEFT))
		{ 
		
    		} 	
		
	}
		
	return ::hit_me(wcpen, dt, attacker, attack_id, target_hitloc);
}	

*/
/* SPECIAL ATTACK */
int
special_attack(object enemy)
{
	object *weps, wep, me;
	mixed* hitresult;
	string how;
        int pen, res, hp1, hp2, spn;
        if(random(2)) return 0;
	me=this_object();
	spn = random(3) + 1;
	if (spn == 1)
	{
	if (enemy->query_prop(LIVE_I_UNDEAD))
	{
		write_file("/d/Cirath/log/reaper_unwield_log",
 			enemy->query_real_name()+" is undead. " + 
 			extract(ctime(time()),4,15)+"\n");
		spn = random(2) + 2;
	}
	else if (enemy->query_weapon(W_RIGHT) || enemy->query_weapon(W_LEFT) ||
		enemy->query_weapon(W_BOTH))
	{	
		tell_watcher(QCTNAME(me)+" starts to concentrate.\n", me);
		weps = enemy->query_weapon(-1);
		wep = weps[random(sizeof(weps))];
		enemy->command("$unwield " + wep->query_name());
		write_file("/d/Cirath/log/reaper_unwield_log",
 			enemy->query_real_name()+", Unwields: " + wep->query_name() + ". " + 
 			extract(ctime(time()),4,15)+"\n");
	}
	else
	{
		write_file("/d/Cirath/log/reaper_unwield_log",
 			enemy->query_real_name()+" has no weapon. " + 
 			extract(ctime(time()),4,15)+"\n");
		spn = 2;
	}	
	
	
	}
	if (spn == 2)
	{
 		hp1 = enemy->query_hp();			// log code
		res = enemy->query_magic_res(MAGIC_I_RES_FIRE);	// log code
 		pen = 500 * (100 - enemy->query_magic_res(MAGIC_I_RES_FIRE)) /100;
		hitresult = enemy->hit_me(pen, MAGIC_DT, me, -1);
		how = "slightly";
	if (hitresult[0] > 5) how = "somewhat";
	if (hitresult[0] > 15) how = "severely";
 
 		hp2 = hp1 - enemy->query_hp();			// log code
 		write_file("/d/Cirath/log/reaper_fire_log",
 			enemy->query_real_name()+", Dam: " + hp2 + ". Res: " + res + 
 			" Pen: " + pen + ". " + extract(ctime(time()),4,15)+"\n");
 	if (enemy->query_prop(LIVE_I_UNDEAD))
 	{
 		command("' You filthy undead! You will burn in hell!");
 	}
	enemy->catch_msg(QCTNAME(me) + " raises both of "+
                     HIS_HER(me) + " hands simultaneously, "+
                     "then brings them down pointing in your "+
                     "general vicinity.\n");
	enemy->catch_msg("The air around you erupts in flames and "+
		     "you are burned " + how + ".\n");
 
	tell_watcher(QCTNAME(me)+" raises both of "+
                     HIS_HER(me) + " hands simultaneously, "+
                     "then brings them down pointing in "+
                     QTNAME(enemy)+ "'s general vicinity.\n",
		me, enemy);
	tell_watcher("The air around " + QTNAME(enemy) + 
		     " erupts in flames and " + HE_SHE(enemy) + 
		     " is burned " + how + ".\n",me, enemy);
 	}
 
 	if (spn == 3)
	{
 		hp1 = enemy->query_hp();			// log code
		res = enemy->query_magic_res(MAGIC_I_RES_AIR);	// log code
 		pen = 700 * (100 - enemy->query_magic_res(MAGIC_I_RES_AIR)) /100;
		hitresult = enemy->hit_me(pen, MAGIC_DT, me, -1);
		how = "";
	if (hitresult[0] > 5) how = " in severe pain";
	if (hitresult[0] > 15) how = " in excruciating pain";
 
 		hp2 = hp1 - enemy->query_hp();			// log code
 		write_file("/d/Cirath/log/reaper_thrown_log",
 			enemy->query_real_name()+", Dam: " + hp2 + ". Res: " + res + 
 			" Pen: " + pen + ". " + extract(ctime(time()),4,15)+"\n");
 	
 	tell_watcher(QCTNAME(me)+" raises the palm of "+
                     HIS_HER(me) + " hands upwards.\n", me);
 	enemy->catch_msg("The feel yourself being picked up by an unnatural force.\n");
 	tell_watcher(QCTNAME(enemy)+" is picked up by an unnatural force.\n",
		me, enemy);
 	enemy->catch_msg("The find yourself hurled across the alley to the south.\n");
 	tell_watcher(QCTNAME(enemy)+" is hurled across the alley to the south.\n",
		me, enemy);
 	enemy->catch_msg("You land flat on your face"+
		     how + ".\n");
 	
 	if(enemy->query_hp() > 0)
 	{
 	tell_room("/d/Cirath/tyr/jail/alley.c", QCTNAME(enemy) + " arrives flying through the air and lands on " + HIS_HER(enemy) + " face.\n", enemy);
        	enemy->move_living("M", "/d/Cirath/tyr/jail/alley.c",1);
 	}
 	}

	if(enemy->query_hp() <= 0) 
		{
			write_file("/d/Cirath/log/reaper_kill_log",
 			enemy->query_real_name()+", Died by reaper special. " + spn 
 			+ ". " + extract(ctime(time()),4,15)+"\n");
			enemy->do_die(me);
 		}
	return 1;
	
	
}