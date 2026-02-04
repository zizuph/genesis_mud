/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * orc.c
 *
 * A young orc found in the orc caves.
 */

#include "/d/Terel/include/Terel.h"

inherit STDMONSTER;

#define WEP_DIR ORC_CAVE_DIR + "weapon/"

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
            WEP_DIR + "bone"
		});
}

/*
 * Function name: create_monster
 * Description:   Create the monster. (standard)
 */
public void
create_monster()
{
    set_name("orc");
    set_adj("young");
    set_race_name("orc");
    set_short("young orc");
    set_long("He is playing with a bone.\n");
    set_stats(({20, 20, 20, 20, 20, 20}));
    set_skill(SS_WEP_CLUB, 20);
    set_skill(SS_PARRY, 20);
    set_skill(SS_DEFENCE, 20);

    SET_MAX_HP;
    set_alignment(-100);
    AGGRESSIVE;
    
    add_prop(OBJ_I_WEIGHT, 75000);
    add_prop(CONT_I_MAX_WEIGHT, 95000);
    add_prop(OBJ_I_VOLUME, 75000);
    add_prop(CONT_I_MAX_VOLUME, 95000);
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
    money = MONEY_MAKE_CC(15 + random(10));
    money->move(TO);
}

/*
 * Function name: equip_actions
 * Description:   Initial commands (e.g. wield sword)
 */
public void
equip_actions()
{
    TO->command("wield bone");
}

