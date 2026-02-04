/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * c_guard.c
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
            RIBOS_DIR + "weapon/gsword",
	    RIBOS_DIR + "armour/h_g_armour"
		});
}

/*
 * Function name: create_monster
 * Description:   Create the monster. (standard)
 */
public void
create_monster()
{
    ::create_monster();
    set_name("borolack");
    set_race_name("human");
    set_adj("confident");
    set_long("He is a very confident honor guard.\n");

    default_config_npc(50);

    SET_MAX_HP;
    
    set_skill(SS_WEP_SWORD, 55);
    set_skill(SS_DEFENCE,   35);
    set_skill(SS_PARRY,     40);
    
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
}
