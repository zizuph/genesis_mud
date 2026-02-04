/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * eremite.c
 *
 * An eremite. Mortricia 920717
 * Modified by Sorgum 941002
 */

#include "/d/Terel/include/Terel.h"

inherit STDMONSTER;

#define ARM_DIR SILVER_DIR + "armour/"

#include <ss_types.h>
#include <money.h>

/*
 * Function name: query_object_list
 * Description:   return list of equipment
 */
public string*
query_object_list()
{
    return ({ARM_DIR + "nightshirt"});
}

/*
 * Function name: create_monster
 * Description:   Create the monster. (standard)
 */
public void
create_monster()
{
    ::create_monster();
    set_name("eremite");
    set_short("eremite");
    set_long("A very old man.\n");
    set_adj("old");
    set_race_name("human");
    set_gender(MALE);

    set_stats(({15, 15, 15, 15, 20, 15}));
    SET_MAX_HP;
    SET_MAX_MANA;
    set_alignment(200);
    set_skill(SS_DEFENCE, random(10) + 20);
    set_skill(SS_UNARM_COMBAT, random(5) + 10);

    set_act_time(30);
    add_act(({"sigh", "cough"}));

    add_prop(LIVE_I_NEVERKNOWN, 1);
    
    set_all_hitloc_unarmed(5);
    set_all_attack_unarmed(10, 10);
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
    MONEY_MAKE_SC(10) -> move(TO);
}

/*
 * Function name: equip_actions
 * Description:   Initial commands (e.g. wield sword)
 */
public void
equip_actions()
{
    TO->command("wear nightshirt");
}
