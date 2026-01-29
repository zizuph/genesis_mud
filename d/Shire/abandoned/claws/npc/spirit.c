
/* /d/Shire/rhudaur/npc/spirit.c
 * This evil Undead spirit will be unkillable by common weapons.
 * If you have a magic weapon, you will easily kill him, increasing
 * the damage done on him. But not all magic weapons though, only 
 * some, which will be found further down in the code.
 * 
 * Some of these functions I borrowed from Nazgul of Gondor.
 * Which was coded by Olorin, Elessar and Dunstable :-)
 * Hopefully none of these will be angry on me :)
 * Sir odin.
 */

inherit "/std/monster"; /* For add_chat etc. */
inherit "/d/Immortal/rogon/open/tell";

#include <const.h>
#include <filter_funs.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "../defs.h"
#include "/d/Shire/moria/skills/skill_types.h"
#include "/d/Shire/common/make_money.h"
#include "/d/Shire/common/lib/evilkill.h"

#define CEX if (!combat_extern) combat_reload()

object last_weapon;
//int has_introduced=1;

create_monster()
{
	if (!IS_CLONE)
	return;
	seteuid(getuid(TO));
        set_name("nobularexus");
	set_short("spirit");
	set_adj("fallen");
	add_adj(({"evil", "many shaped"}));
	set_title("the Terror of Rhudaur, former servant of Morgoth");
	set_race_name("spirit");
	set_long(
		"This is an evil undead being which is taking many shapes. It is a ghost\n"+
		"of old times and radiate great might from fallen days, long forgotten.\n"+
		"It is huge of built and looks strong. It must have dwelt here ever since\n"+
		"the days of Morgoth, hidden from the might of the Elves in those days.\n");
	
	set_stats(({140, 170, 140, 100, 125, 130}));

	TO->setup_skills();

	set_skill(SS_WEP_SWORD, 	   100);
	set_skill(SS_DEFENCE, 			80);
	set_skill(SS_PARRY, 			90);
	set_skill(SS_2H_COMBAT, 	   100);
	set_skill(SS_AWARENESS, 		80);
	set_skill(SS_BLIND_COMBAT, 		80);
	set_skill(SS_DIS_FOE_ARMED, 	80);
	//set_skill(SS_FUMBLE,			90);
	//set_skill(SS_DIS_FOE_UNARMED,	70);

	add_prop(CONT_I_WEIGHT, 	  70000);
	add_prop(CONT_I_HEIGHT, 	    250);
	add_prop(LIVE_I_UNDEAD, 	    100);
	add_prop(LIVE_I_SEE_DARK, 	 	 10);
	add_prop(LIVE_I_QUICKNESS, 	 	 10);

/* Some magic resistance properties */
	add_prop(OBJ_I_RES_POISON, 		100);
	add_prop(OBJ_I_RES_DEATH,		 80);
	add_prop(OBJ_I_RES_AIR, 		 30);
	add_prop(OBJ_I_RES_LIFE,		 20);
	add_prop(OBJ_I_RES_MAGIC,		 50);
 	add_prop(OBJ_I_RES_EARTH,		 10);

	add_prop(LIVE_I_NO_CORPSE, 		  1);
	add_prop(NPC_I_NO_LOOKS, 		  1);
	add_prop(MAGIC_AM_ID_INFO,
		({ "This spirit, servant of Morgot in his prosporous days is of great evil.\n", 1,
			"A fallen spirit it is, hidden from the destruction in the days of the\n"+
			"high elves, when they destroyed Morgoth with the help of the Valars and\n"+
			"maiars. It is one of the few spirits that escaped the destruction of \n"+
			"Thangorodrim in the Great Battle in the first age.\n", 10,
			"The spirit is still capable, and strong as ever, untouched by age as it is.\n"+
			"It is only killable by some magic weapons, and normal weapons will do little\n"+
			"or no harm on him, since he isnt of living flesh.\n", 40,
		}));

	set_attack_chance(10);
	set_aggressive(1);

	set_alarm(3.0,0.0,"arm_me",1);
	add_prop("_npc_i_no_ranger_brawl", 1);
	set_alignment(-670 - random(100));

	set_act_time(6);
	add_act("emote smears the blade on his sword and grins evilly!");
	add_act("say Thou witless fool. Be gone or be dead!");
	//add_act("kill elf");
-- More -- 100 -- (<cr> t b r a <num> q x !<cmd> h ?) -- 
	//add_act("kill dwarf");
	//add_act("kill human");
	//add_act("kill goblin");
	//add_act("kill gnome");

	set_cact_time(10);
	add_cact("say I will slaughter you and feed on your soul!!");
	add_cact("say You are even more pitful then the old fool!");
	add_cact("laugh evil");

	make_platinum(2+random(4));
	make_gold(5+random(10));
	make_silver(10+random(30));

	trig_new("%w 'introduces' %s", "react_introduce");

}
/* 
void
react_introduce(string person, string who)
{
	if (!has_introduced)
	{
		set_alarm(3.0,0.0,"introduce_me");
		has_introduced=1;
		set_alarm(3.0,0.0,"remove_int");
	}
}

void
introduce_me()
{
	command("introduce me");
}

void
remove_int()
{
	has_introduced=0;
}
*/
int
query_magic_res(string prop)
{
	
  	if (prop == MAGIC_I_RES_WATER 	||
		prop == MAGIC_I_RES_POISON 	||
		prop == MAGIC_I_RES_ACID)
		return 90;
	else
		return 0;

}

void
arm_me()
{
   	//clone_object(RHUD_WEP + "spir_swo")->move(TO);
	//command("wield sword");
	clone_object(RHUD_ARM + "spir_clo")->move(TO);
	command("wear cloak");
	clone_object(RHUD_ARM + "spir_pla")->move(TO);
	command("wear plate");
	clone_object(RHUD_ARM + "spir_hel")->move(TO);
	command("wear helmet");
/*	clone_object(RHUD_ARM + "spir_boo")->move(TO);
	command("wear boots");
*/

}
/*
void
do_specials(object who)
{
	switch(random(3))
	{
		case 0:
			if((SKILL_DIR+"fumble")->fumble(who, TO))
			break;
		case 1:
			if((SKILL_DIR+"disarm")->disarm_foe_armed(who, TO))
			break;
		case 2:
			command("scream");
			break;
	}
}
*/
public mixed
hit_me(int wcpen, int dt, object attacker, int attack_id)
{
   	mixed hitres;
	int dam;

	if(wcpen > 100)
	wcpen = 100;

	if (dt != MAGIC_DT && attack_id == -1)
	{
		hitres = ::hit_me(wcpen, dt, attacker, attack_id);
-- More -- 200 -- (<cr> t b r a <num> q x !<cmd> h ?) -- 
	}
	else 
		hitres = ::hit_me(wcpen, dt, attacker, attack_id);
/*
 * Special attacks are reduced with a huge amount since I dont want him killed
 *	by normal, unmagical weapons.
 * Sir Odin.
 */
	return hitres;

}

/*
int
query_not_attack_me(object att, int att_id)
{
   object  weapon = att->query_weapon(att_id);
   mixed  *mag_arr;
   int     mid;
   
   if (!weapon)
      return 1;
   last_weapon = weapon;
   if (!weapon->query_prop(OBJ_I_IS_MAGIC_WEAPON)) 
   {
      if (!random(10))
         tell_room(ENV(TO),QCTNAME(att)+"'s "+weapon->query_name()
           + " seems to have no effect against the spirit!\n",att);
   }
   mag_arr = weapon->query_prop(MAGIC_AM_MAGIC);
   if ((mid = member_array("undead-slaying",mag_arr)) > 0)
   {
      if (random(mag_arr[mid-1]) == 0)
      return 0;
   }
   if ((mid = member_array("enchantment",mag_arr)) > -1) 
   {
      if (random(mag_arr[mid-1]) < 3)
      return 0;
   }
   tell_room(ENV(TO), BSN("The magic in the " + check_call(weapon->short()) +
         " seems to have no effect on the spirit."));
   say("Your lousy " + check_call(weapon->short()) + " does not worry me, mortal!\n");
   return 1;
}
*/

int
do_die(object killer)
{
	if(query_hp() > 0)
		return 0;
	if(!killer)
		killer = previous_object();
	tell_object(killer, "You run your weapon straight through the body of the spirit.\n");
	tell_room(ENV(TO),BS(QCTNAME(killer)+" runs "+HIS_HER(killer)+" weapon through the body of the cloacked spirit.\n"), killer);
	tell_room(ENV(TO), BS(
			"The cloak falls to the ground. You stare in dismay at the plate and helm, for it is empty "+
			"as the dark sky. No body, nor scale is left behind!\n") + BS("Thunder roles over the sky, "+
			"and a cold wind blows over the plains. A sudden flash of lightning strikes the ground infront "+
			"of you. It all dies out just seconds later.\n"));
	CEX; combat_extern->cb_death_occured(killer);
	killer->notify_you_killed_me(TO);
	move_all_to(ENV(TO));
	TO->remove_object();
	return 1;
}

int
query_knight_prestige()
{
	return 100;
}

/*
int
special_attack(object who)
{
	int dam;
	mixed *did_hurt;

	switch(random(3))
	{
		case 0:
			do_specials(who);
			return 1;
			break;
		case 1:
			tellem(TO, who, 
				"$N $glare haughtily at #n!\n");
			who->heal_hp(-random(100));
			return 1;
			break;			
		case 2:
			tellem(TO, who,
				"$N $touch #n with $p cold hands, draining energy from #o!\n");
			who->add_mana(-(30 + random(60)));
			return 1;
			break;
	}
	return 0;
}
*/

> 