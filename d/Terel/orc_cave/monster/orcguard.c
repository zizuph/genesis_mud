/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * orcguard.c
 *
 * An orcguard found in the orc caves.
 */

#include "/d/Terel/include/Terel.h"

inherit STDMONSTER;

#define WEP_DIR ORC_CAVE_DIR + "weapon/"
#define ARM_DIR ORC_CAVE_DIR + "armour/"

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
	WEP_DIR + "axe",
        ARM_DIR + "helmet",
        ARM_DIR + "boots"	    
		});
}

/*
 * Function name: create_monster
 * Description:   Create the monster. (standard)
 */
public void
create_monster()
{
    if (!IS_CLONE)
	return;
    set_name(({"orcguard","guard"}));
    set_adj("nasty");
    set_race_name("orc");
    set_short("nasty orcguard");
    set_long("He looks quite strong.\n");
    set_stats(({55, 55, 55, 55, 55, 55}));

    set_skill(SS_WEP_AXE, 55);
    set_skill(SS_PARRY, 55);
    set_skill(SS_DEFENCE, 55);
    AGGRESSIVE;

    SET_MAX_HP;
    set_alignment(-150);
    add_prop(OBJ_I_WEIGHT, 100000);
    add_prop(OBJ_I_VOLUME, 100000);
    add_prop(CONT_I_MAX_WEIGHT, 155000);
    add_prop(CONT_I_MAX_VOLUME, 155000);
    add_prop(LIVE_I_SEE_DARK,1);
    set_all_hitloc_unarmed(query_average_stat() / 2);
}

/*
 * Function name: equip_me
 * Description:   Give me some equipment.
 */
public void
equip_me()
{
    object money;

    ::equip_me();
    FIX_EUID;
    money = MONEY_MAKE_CC(200 + random(200));
    money->move(TO);
}

/*
 * Function name: equip_actions
 * Description:   Initial commands (e.g. wield sword)
 */
public void
equip_actions()
{
    TO->command("wear all");
    TO->command("wield all");    
}
