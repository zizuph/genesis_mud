/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * steel_guard.c
 *
 * an elf guard 920921 Redhawk
 * Modified by Sorgum 941002
 */

#include "/d/Terel/include/Terel.h"
inherit LOD_DIR + "monster/legion_soldier";

#include <ss_types.h>

/*
 * Function name: query_object_list
 * Description:   return list of equipment
 */
public string*
query_object_list()
{
    return ({LOD_DIR + "armour/steel_chainmail",
	     LOD_DIR + "armour/steel_helmet",
	     LOD_DIR + "armour/steel_boots",
	     LOD_DIR + "weapon/steel_sword"});
}

/*
 * Function name: create_monster
 * Description:   Create the monster. (standard)
 */
public void
create_monster()
{
    ::create_monster();
    set_name ("guard");
    add_name("steel_guard");
    set_short("elf guard");
    set_long("An elf guard that is a member of the legion of darkness. " +
	     "He looks like he is quite confident with himself.\n");
    set_adj("noble");
    set_race_name("elf");
    set_gender(MALE);
    set_alignment(-100);
    set_stats(({50, 50, 50, 40, 40, 40}));
    SET_MAX_HP;
    AGGRESSIVE;
    set_skill(SS_DEFENCE,      50 + random(11));
    set_skill(SS_UNARM_COMBAT, 35 + random(11));
    set_skill(SS_PARRY,        55 + random(11));
    set_skill(SS_WEP_SWORD,    60 + random(11));
}
