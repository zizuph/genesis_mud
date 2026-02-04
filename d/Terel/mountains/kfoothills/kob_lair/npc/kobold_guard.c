/*
 *  kobold_guard.c
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
    set_name("guard");
    set_adj(face());
    set_gender(MALE);
    set_long("A short dog-faced creature with grey scaly skin. It has " 
      + "two small light-coloured horns on its head, glowing red " 
      + "eyes and a non-prehensile tail. He looks well fed and gives " 
      + "the presence of a trained fighter ready to protect his lair.\n");

    set_base_stat(SS_STR, 23 + random(5) );
    set_base_stat(SS_DEX, 23 + random(5) );
    set_base_stat(SS_CON, 23 + random(5) );
    set_base_stat(SS_INT, 18 + random(3) );
    set_base_stat(SS_WIS, 18 + random(3) );
    set_base_stat(SS_DIS, 18 + random(3) );

    add_prop(CONT_I_WEIGHT, 25000);
    add_prop(CONT_I_HEIGHT, 100);
    add_prop(CONT_I_VOLUME, 25000);
    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(LIVE_I_SEE_DARK, 5);
    add_prop(NPC_I_NO_FEAR, 1);

    set_restrain_path(KOB_LAIR_PATH);
    set_random_move(60);
    
    set_aggressive(1);
    set_attack_chance(50);
    set_alignment(-100 - random(100) );
   
    set_skill(SS_WEP_CLUB, 25 + random(10) );
    set_skill(SS_WEP_AXE, 15 + random(10) );
    set_skill(SS_WEP_SWORD, 15 + random(10) );
    set_skill(SS_WEP_KNIFE, 20 + random(10) );
    set_skill(SS_WEP_POLEARM, 25 + random(10) );
    set_skill(SS_2H_COMBAT, 25 + random(10) );
    set_skill(SS_DEFENCE, 20 + random(10) );
    set_skill(SS_PARRY, 20 + random(10) );
    set_skill(SS_AWARENESS, 7 + random(5) );
    arm_me();
    set_default_answer(this_object()->short() 
        + " appraises you and goes bark, yip, bark!");

    add_act( "say roof, roof" );
    add_act( "say Graught, yip, trecian!" );
    add_act( "emote growls" );
    add_act( "emote barks and growls." );
    add_act( "say Ront ront Eeeioo." );
    set_act_time(25);
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
    MONEY_MAKE( random(6), "silver")->move(TO);
    MONEY_MAKE( 3 + random(4), "copper")->move(TO);

    switch(random(5))
    {
        case 0:
            clone_object(WEAPON + "sword")->move(TO);
            break;

        case 1:
            clone_object(WEAPON + "club")->move(TO);
            break;

        case 2:
            clone_object(WEAPON + "knife")->move(TO);
            break;

        case 3:
            clone_object(WEAPON + "axe")->move(TO);
            break;

        case 4:
            clone_object(WEAPON + "spear")->move(TO);
            break;

    }
    clone_object(ARMOUR + "ragged_fur")->move(TO);

    command("wear all");
    command("wield all");
    return;
}
