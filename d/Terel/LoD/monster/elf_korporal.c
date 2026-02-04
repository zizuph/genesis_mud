/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * elf_korporal.c
 *
 * an elf corpral in the legion Redhawk 920921
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
    return ({LOD_DIR + "armour/splint_mail",
            LOD_DIR + "armour/splint_helmet",
	    LOD_DIR + "weapon/short_sword"});
}

/*
 * Function name: create_monster
 * Description:   Create the monster. (standard)
 */
public void
create_monster()
{
    ::create_monster();
    set_name("corporal");
    add_name("elf_korporal");
    set_short("elf corporal");
    set_long("An elf corporal in the legion of darkness army.\n");
    set_adj("evil");
    set_race_name("elf");
    set_gender(MALE);
    set_alignment(-100);

    set_stats(({30, 30, 30, 30, 25, 25}));
    SET_MAX_HP;
    
    set_skill(SS_DEFENCE,      40 + random(5));
    set_skill(SS_UNARM_COMBAT, 25 + random(5));
    set_skill(SS_PARRY,        45 + random(5));
    set_skill(SS_WEP_SWORD,    40 + random(5));
    AGGRESSIVE;
}
