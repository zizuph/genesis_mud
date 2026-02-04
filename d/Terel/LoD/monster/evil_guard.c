/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * evil_guard
 *
 * an elf sergeant in the legion Redhawk 920926
 * Modified by Sorgum 941029
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
    return ({LOD_DIR + "armour/evil_boots",
	     LOD_DIR + "armour/evil_chainmail",
	     LOD_DIR + "weapon/evil_sword"});
}

/*
 * Function name: create_monster
 * Description:   Create the monster. (standard)
 */
public void
create_monster()
{
    ::create_monster();
    set_name("guard");
    add_name("evil_guard");
    set_short("evil looking guard");
    set_long("A guard that is a member of the powerful and evil " +
	     "legion of darkness. \n");
    set_gender(MALE);
    set_adj("evil");
    set_race_name("human");
    set_alignment(-200);
    set_stats(({40, 40, 40, 30, 30, 30}));

    set_skill(SS_UNARM_COMBAT, 25);
    set_skill(SS_WEP_SWORD,    35);
    set_skill(SS_DEFENCE,      25);
    set_skill(SS_PARRY,        25);    
    set_skill(SS_WEP_CLUB,     80);
    set_skill(SS_2H_COMBAT,    80);
    set_skill(SS_BLIND_COMBAT, 10);
    set_skill(SS_AWARENESS,    10);
    set_skill(SS_LANGUAGE,     60);
    set_skill(SS_DEFENCE,      20);
    set_skill(SS_WEP_POLEARM, 100);    
    
    SET_MAX_HP;
    SET_MAX_MANA;

    AGGRESSIVE;
}
