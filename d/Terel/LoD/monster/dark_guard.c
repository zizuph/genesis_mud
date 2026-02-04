/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * dark_guard.c
 *
 * A dark guard for the legion of darkness
 * Sorgum 941029
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
    return ({LOD_DIR + "armour/dark_helmet",
             LOD_DIR + "armour/dark_chainmail",
	     LOD_DIR + "armour/dark_shield",
	     LOD_DIR + "weapon/dark_sword"});
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
    add_name("dark_guard");
    set_short("legion guard");
    set_long("A human guard that guards the entrance to these evil quarters " +
	     "of the legion of darkness.\n");
    set_adj("evil");
    set_race_name("human");
    set_gender(MALE);
    set_alignment(-100);
   
    set_stats(({60, 70, 70, 50, 40, 40}));
    SET_MAX_HP;
    AGGRESSIVE;
    
    set_skill(SS_DEFENCE,      55 + random(11));
    set_skill(SS_UNARM_COMBAT, 30 + random(11));
    set_skill(SS_PARRY,        55 + random(11));
    set_skill(SS_WEP_SWORD,    95 + random(5));
}
