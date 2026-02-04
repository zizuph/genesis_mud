/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * strongguard.c
 *
 * Vader
 * Modified by Sorgum 950707
 */

#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;

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
    set_race_name("human");
    set_adj("noble");
    set_short("strong noble knight");
    set_long("He is strong, noble, and confident. He guards the " +
	     "entrance to the treasury, and you can bet few will get passed " +
	     "him.\n");

    set_stats(({60 + random(20), 60 + random(20), 50 + random(30), 50,50,50}));
    set_all_hitloc_unarmed(25);

    set_skill(SS_WEP_SWORD, 50);
    set_skill(SS_DEFENCE, 70);
    set_skill(SS_PARRY, 65);
    
    SET_MAX_HP;
    set_alignment(250);

    set_act_time(5);
    add_act("say There isn't a chance in hell of you getting passed me!");
    add_act("grin");
    add_act("say Who the hell do you think you are? Get out of here.");
    add_act("say I'll never let you pass. The king's treasures are " +
	    "off limits to you.");
    equip_me();
}

void lambaste(object tp) { }

/*
 * Function name: equip_me
 * Description:   Give me some equipment.
 */
public void
equip_me()
{
    ::equip_me();
    equip_actions();
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


