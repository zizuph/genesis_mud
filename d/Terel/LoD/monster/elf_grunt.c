/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * elf_grunt.c
 *
 * an elf warrior 920921 Redhawk
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
    
    set_name("warrior");
    add_name("elf_grunt");
    set_short("elf legion warrior");
    set_long("An apprentice elf warrior that is a member of the " +
	     "legion of darkness\n");
    set_adj("evil");
    set_race_name("elf");
    set_gender(MALE);
    set_alignment(-50);

    set_stats(({25, 25, 25, 25, 25, 25}));
    SET_MAX_HP;
    
    set_skill(SS_DEFENCE,      40 + random(5));
    set_skill(SS_UNARM_COMBAT, 25 + random(5));
    set_skill(SS_PARRY,        40 + random(5));
    set_skill(SS_WEP_SWORD,    20 + random(5));
    AGGRESSIVE;

    set_all_hitloc_unarmed(15);
    set_all_attack_unarmed(15, 15);
}
