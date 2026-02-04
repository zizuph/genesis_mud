/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * elf_sergeant.c
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
    return ({LOD_DIR + "armour/steel_chainmail",
            LOD_DIR + "armour/steel_boots",
	    LOD_DIR + "armour/steel_helmet",
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
    set_name("sergeant");
    add_name("elf_sergeant");
    set_short("elf sergeant");
    set_long("An elf sergeant in the legion of darkness army.\n");
    set_adj("swift");
    set_race_name("elf");
    set_gender(MALE);
    set_alignment(-100);

    set_stats(({40, 40, 40, 40, 30, 30}));
    SET_MAX_HP;
    
    set_skill(SS_DEFENCE,      50 + random(5));
    set_skill(SS_UNARM_COMBAT, 35 + random(5));
    set_skill(SS_PARRY,        55 + random(5));
    set_skill(SS_WEP_SWORD,    50 + random(5));
    AGGRESSIVE;
}
