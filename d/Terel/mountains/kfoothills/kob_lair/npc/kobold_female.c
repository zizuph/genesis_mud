/*
 *  kobold_female.c
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
void arm_me();

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
    set_name("kobold");
    set_adj(face());
    set_gender(FEMALE);
    set_long("A small dog-faced creature with grey scaly skin. she has " 
      + "two small light-coloured horns on its head, glowing red eyes " 
      + "and a non-prehensile tail. She looks well fed and moves " 
      + "with cunning grace.\n");

    set_base_stat(SS_STR, 14 + random(5) );
    set_base_stat(SS_DEX, 14 + random(5) );
    set_base_stat(SS_CON, 14 + random(5) );
    set_base_stat(SS_INT, 12 + random(3) );
    set_base_stat(SS_WIS, 12 + random(3) );
    set_base_stat(SS_DIS, 12 + random(3) );

    add_prop(CONT_I_WEIGHT, 20000);
    add_prop(CONT_I_HEIGHT, 75);
    add_prop(CONT_I_VOLUME, 20000);
    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(LIVE_I_SEE_DARK, 5);

    set_aggressive(1);
    set_attack_chance(50);
    set_alignment(-100 - random(100) );
   
    set_skill(SS_WEP_CLUB, 22 + random(10) );
    set_skill(SS_WEP_AXE, 12 + random(10) );
    set_skill(SS_WEP_SWORD, 12 + random(10) );
    set_skill(SS_WEP_KNIFE, 17 + random(10) );
    set_skill(SS_WEP_POLEARM, 22 + random(10) );
    set_skill(SS_2H_COMBAT, 22 + random(10) );
    set_skill(SS_DEFENCE, 17 + random(10) );
    set_skill(SS_PARRY, 17 + random(10) );
    set_skill(SS_AWARENESS, 6 + random(5) );
    arm_me();
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
    faces = ({"stern", "robust", "knavish", "sneaky", "rascally",
        "deceitful", "unscrupulous", "arrant", "treacherous", 
        "foul", "perfidious", "praetorian", "snide", "bent"});
        
    return faces[random(sizeof(faces))];
}

/*
 * Function name: arm_me
 * Description  : Clone inventory and weapons and wield/wear.
 * Arguments    : n/a
 * Returns      : n/a
 */
void
arm_me()
{
    FIX_EUID;
    MONEY_MAKE( 1 + random(4), "copper")->move(TO);

    switch(random(2))
    {
        case 0:
            clone_object(WEAPON + "club")->move(TO);
            break;

        case 1:
            clone_object(WEAPON + "knife")->move(TO);
            break;
    }
    clone_object(ARMOUR + "ragged_fur")->move(TO);

    command("wear all");
    command("wield all");
    return;
}
