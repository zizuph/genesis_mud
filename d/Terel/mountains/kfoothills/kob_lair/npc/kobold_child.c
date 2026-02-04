/*
 *  kobold_child.c
 *
 *  Britanica 160322
 */
#pragma strict_types
 
#include "/d/Terel/include/Terel.h"
#include "../include/cave_defs.h"
#include <ss_types.h>
#include <options.h>
#include <money.h>

inherit STDMONSTER;
inherit "/std/act/domove";

string face();

/*
 * Function name: query_option
 * Description  : Do not use unarmed combat option.
 * Arguments    : n/a
 * Returns      : 1 for OPT_UNARMED_OFF
 */
int
query_option(int opt)
{
    return (opt == OPT_UNARMED_OFF);
}

/*
 * Function name: create_monster
 * Description  : constructor.
 * Arguments    : n/a
 * Returns      : n/a
 */
void
create_monster()
{

    set_race_name("kobold");
    set_name("pup");
    set_adj(face());
    set_gender(random(2));
    set_long("A tiny dog-faced creature with grey scaly skin. It has two " 
      + "nubs on its head that look like sprouting horns, glowing red " 
      + "eyes and a non-prehensile tail.\n");

    set_base_stat(SS_STR, 10 + random(5) );
    set_base_stat(SS_DEX, 10 + random(5) );
    set_base_stat(SS_CON, 10 + random(5) );
    set_base_stat(SS_INT, 2 + random(3) );
    set_base_stat(SS_WIS, 2 + random(3) );
    set_base_stat(SS_DIS, 2 + random(3) );

    add_prop(CONT_I_WEIGHT, 10000);
    add_prop(CONT_I_HEIGHT, 45);
    add_prop(CONT_I_VOLUME, 10000);
    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(LIVE_I_SEE_DARK, 5);

    set_aggressive(1);
    set_attack_chance(50);
    set_alignment(25 - random(100) );
}

/*
 * Function name: face
 * Description  : return a randomized face.
 * Arguments    : n/a
 * Returns      : string with face description
 */
string 
face()
{
    string *faces;
    faces = ({"young", "tiny", "little", "hatchling"});
        
    return faces[random(sizeof(faces))];
}
