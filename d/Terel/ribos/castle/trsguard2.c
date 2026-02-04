/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * trsguard2.c
 *
 * Treasure guards
 *
 * Vader
 * Modified by Sorgum 950707
 */

#include "/d/Terel/include/Terel.h"
#include "local.h"
inherit CASTLE_DIR + "monster/trsguard";
inherit "/std/act/action";     
inherit "/std/act/seqaction";
inherit "/std/act/domove";     

#include <ss_types.h>
#include <money.h>

/*
 * Function name: query_object_list
 * Description:   return list of equipment
 */
public string*
query_object_list()
{
    return ({
            RIBOS_DIR + "weapon/t_sword",
		RIBOS_DIR + "armour/t_armour",
		CASTLE_DIR + "obj/treas_key"
		});
}

/*
 * Function name: create_monster
 * Description:   Create the monster. (standard)
 */
public void
create_monster()
{
    set_name("knight");
    add_name("scrappy");
    set_race_name("human");
    set_adj("noble");
    set_short("strong noble knight");
    set_long("He is strong, noble, and confident.  He guards the " +
	     "entrance to\nthe treasury, and you can bet few will get past " +
	     "him.\n");

    set_stats(({60 + random(20), 60 + random(20), 50 + random(30), 50,50,50}));
    set_all_hitloc_unarmed(25);

    set_skill(SS_WEP_SWORD, 50);
    set_skill(SS_DEFENCE,   70);
    set_skill(SS_PARRY,     65);
    
    SET_MAX_HP;
    set_alignment(250);
    
    set_act_time(5);
    add_act("say There isn't a chance in hell of you getting past me!");
    add_act("grin");
    add_act("say Beat it!");
}


void
lambaste(object tp)
{
    object obj;
    object *obj_list;
    int i;

    obj_list = all_inventory(ETO);
    
    command("close door");
    command("lock door");    
    command("shout Hey!  You have no business being in this room!");
    command("shout Get " + OBJECTIVE(tp) + " boys!");

    TO->attack_object(tp);
    
    for (i = 0; i < sizeof(obj_list); i++) {
	obj = obj_list[i];
	if (function_exists("lambaste", obj) && (obj != TO)) {
	    TO->team_join(obj);
	    tp->attack_object(obj);
	    obj->command("shout Die, you lousy scum!");
	}
    }
}

/*
 * Function name: equip_me
 * Description:   Give me some equipment.
 */
public void
equip_me()
{
    ::equip_me();
    FIX_EUID;
    MONEY_MAKE_SC(random(10)) -> move(TO);
}

/*
 * Function name: equip_actions
 * Description:   Initial commands (e.g. wield sword)
 */
public void
equip_actions()
{
    TO->command("wield sword");
    TO->command("wear armour");
}


