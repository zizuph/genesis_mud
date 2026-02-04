/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * iron_guard.c
 * 
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
    return ({LOD_DIR + "armour/iron_chainmail",
	     LOD_DIR + "armour/iron_helmet",
	     LOD_DIR + "armour/leather_boots",
	     LOD_DIR + "weapon/iron_sword"});
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
    add_name("iron_guard");
    set_race_name("human");
    set_short(query_race_name() + " guard");
    set_long("A guard that is a member of the legion of darkness. " +
	     "he looks like he's quite confident with himself.\n");
    set_adj("noble");

    set_gender(MALE);
    AGGRESSIVE;

    set_stats(({40, 40, 40, 30, 30, 30}));
    SET_MAX_HP;
    
    set_skill(SS_DEFENCE,      50 + random(11));
    set_skill(SS_UNARM_COMBAT, 35 + random(11));
    set_skill(SS_PARRY,        55 + random(11));
    set_skill(SS_WEP_SWORD,    45 + random(11));
}
