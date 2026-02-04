/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * w_knight.c
 *
 * Vader
 * Modified by Sorgum 950602
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
            RIBOS_DIR + "weapon/ssword",
	    RIBOS_DIR + "armour/s_armour",
            RIBOS_DIR + "armour/helmet",
            RIBOS_DIR + "armour/boots"
		});
}

/*
 * Function name: create_monster
 * Description:   Create the monster. (standard)
 */
public void
create_terel_monster()
{
    set_name("knight");
    set_race_name("human");
    set_adj("nervous");
    set_long("He is nervous.  His job is to protect what few people "
	     + "remain here.\n");

    default_config_npc(50 +random(40));

    SET_MAX_HP;
    
    set_skill(SS_DEFENCE,   40);
    set_skill(SS_PARRY,     48);
    set_skill(SS_WEP_SWORD, 50);

    set_chat_time(1);
    add_chat("I hate this job.  Making me risk my life for no one!");
    add_chat("If that thing gets out, we're all dead!");
    add_chat("You shouldn't be here.....It's not safe!");

    set_random_move(10);
    set_alignment(100);
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
    MONEY_MAKE_SC(50) -> move(TO);
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
    TO->command("wear helmet");
    TO->command("wear boots");
}
