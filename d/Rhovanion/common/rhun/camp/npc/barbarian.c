/*
 * /d/Rhovanion/common/rhun/camp/npc/barbarian.c
 *
 * The standard barbarian found in the camp.
 */

inherit "/std/monster";

#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <filter_funs.h>
#include "/d/Rhovanion/defs.h"
#include "/d/Rhovanion/lib/kill_log.h"

#define FDES ({"dark","black","dangerous","strong"})
#define SDES ({"evil","stupid","fat","experienced"})

void
create_monster()
{
    object  ob;
    int     ss, sd, sc, si, sw, sds;
    string  fdes, sdes;
    
    set_race_name("barbarian");
    fdes = ONE_OF_LIST(FDES);
    sdes = ONE_OF_LIST(SDES);
    set_adj(sdes);
    set_adj(fdes);
    set_short(fdes + " " + sdes + " barbarian");
    set_name("_barbarian_");
    
    ss = 80 + random(40);
    sd = 80 + random(40);
    sc = 80 + random(40);
    si = 80 + random(40);
    sw = 80 + random(40);
    sds = 80 + random(40);
    
    set_alignment(-(ss+sd+sc+si+sw+sds));
    set_gender(G_MALE);
    set_long("This barbarian seems to be an easterling. He has come " +
	     "from the far east to join Sauron's army, together with " +
	     "the rest of this band of rabble. They have travelled a " +
	     "long way and now they are enjoying some rest before they " +
	     "continue on their way to Mordor.\n");
    
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(CONT_I_WEIGHT, 72*1000);
    add_prop(CONT_I_VOLUME, 74*1000);
    add_prop(CONT_I_HEIGHT, 174);
    add_prop(LIVE_I_SEE_DARK, 6);
    set_stats(({ss, sd, sc, si, sw, sds}));
    set_hp(query_max_hp());
    
    set_skill(SS_DEFENCE, 60 + random(31));
    set_skill(SS_BLIND_COMBAT, 40 + random(21));
    set_skill(SS_PARRY, 60 + random(31));
    set_skill(SS_WEP_AXE, 60 + random(41));
    set_skill(SS_AWARENESS, 100);
    
    set_act_time(3);
    add_act("grin");
    add_act("kick all sad");
    add_act("ponder");
    add_act("say Get lost!");
    add_act("curse");
    
    set_cact_time(1);
    add_cact("grin");
    add_cact("kick all sad");
    add_cact("ponder");
    add_cact("say Get lost!");
    add_cact("curse");
    
    set_alarm(1.0, 10.0, "tryattack");
}

void
arm_me()
{
    object  ob;
    
    ob = clone_object(CAMP_DIR + "wep/staxe");
    ob->move(this_object());
    command("wield axe");

    ob = clone_object(CAMP_DIR + "arm/stshield");
    ob->move(this_object());
    command("wear shield");

    ob = clone_object(CAMP_DIR + "arm/sthelmet");
    ob->move(this_object());
    command("wear helmet");

    ob = clone_object(CAMP_DIR + "arm/stmail");
    ob->move(this_object());
    command("wear platemail");

    ob = clone_object(CAMP_DIR + "arm/stleggings");
    ob->move(this_object());
    command("wear leggings");
}

void
attacked_by(object enemy)
{
    command("say Insolent " + lower_case(enemy->query_nonmet_name()) + "!"+
	    " I will kill you for this, slowly and painfully!");
}

void
do_die(object killer)
{
    command("scream");
    command("say You killed me!");
    command("point " + lower_case(killer->query_nonmet_name()));
    ::do_die(killer);
}

/* 
 * Function name: special_attack
 * Description:   A special attack, which works once every five rounds.
 * Arguments:     enemy - the current enemy
 * Returns:       1 if the attack was used, 0 otherwise
 */

int
special_attack(object enemy)
{
    mixed   *hitloc;
    int     dam, ac, dex_st;
    object  wielded;
    
    if (!random(5))
	return 0;
    wielded = TO->query_weapon(W_RIGHT);
    if (wielded && (wielded->query_wt() == W_AXE))
    {
	dex_st = enemy->query_stat(SS_DEX);
	tell_watcher(QCTNAME(this_object()) +
		     " grins cruelly as his axe cuts into " +
		     QTNAME(enemy) + ".\n", TO, enemy);
	enemy->catch_msg(QCTNAME(this_object()) + " grins cruelly as his "+
			 "axe cuts into your side.\n");
	dam = random(400) - (random(900) * dex_st) / 100;
	if (dam < 0) 
	    dam=0;
	enemy->set_hp(enemy->query_hp() - dam);
	return 1;
    }
    return 0;
}

void tryattack()
{
    object  *list;
    int     i, r;
    
    if (TO->query_enemy())
	return; 
    list = FILTER_LIVE(all_inventory(environment(TO)))-({TO});
    for(i = 0; i < sizeof(list); i++)
	if ((list[i]->query_name() != "_barbarian_") &&
	    (list[i]->query_invis() == 0))
	{
	    command("kill " + lower_case(list[i]->query_name()));
	    return;
	}
}


