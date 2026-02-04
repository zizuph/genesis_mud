/*
 * kobold_chieftain.c
 *
 * The chieftain hold the key to the storeroom
 *
 * Britanica 160322
 */
#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include "../include/cave_defs.h"
#include <ss_types.h>
#include <options.h>
#include <money.h>

inherit STDMONSTER;
inherit "/std/act/domove";

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
 * Description  : return a randomized face.
 * Arguments    : n/a
 * Returns      : n/a
 */
void
create_monster()
{
    set_race_name("kobold");
    set_name("chieftain");
    set_adj("large");
    set_gender(MALE);
    set_long("A large dog-faced creature with grey scaly skin. It has " 
      + "two small light-coloured horns on its head, glowing red eyes " 
      + "and a non-prehensile tail.  He looks well fed and gives " 
      + "the presence of the leader of the kobolds in this lair.\n");

    set_base_stat(SS_STR, 25 + random(5) );
    set_base_stat(SS_DEX, 35 + random(5) );
    set_base_stat(SS_CON, 25 + random(5) );
    set_base_stat(SS_INT, 20 + random(3) );
    set_base_stat(SS_WIS, 20 + random(3) );
    set_base_stat(SS_DIS, 20 + random(3) );

    add_prop(CONT_I_WEIGHT, 30000);
    add_prop(CONT_I_HEIGHT, 110);
    add_prop(CONT_I_VOLUME, 30000);
    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(LIVE_I_SEE_DARK, 5);
    add_prop(NPC_I_NO_FEAR, 1);

    set_aggressive(1);
    set_attack_chance(50);
    set_alignment(-100 - random(100) );
   
    set_skill(SS_WEP_CLUB, 30 + random(10) );
    set_skill(SS_WEP_AXE, 20 + random(10) );
    set_skill(SS_WEP_SWORD, 20 + random(10) );
    set_skill(SS_WEP_KNIFE, 25 + random(10) );
    set_skill(SS_WEP_POLEARM, 30 + random(10) );
    set_skill(SS_2H_COMBAT, 30 + random(10) );
    set_skill(SS_DEFENCE, 25 + random(10) );
    set_skill(SS_PARRY, 25 + random(10) );
    set_skill(SS_AWARENESS, 15 + random(5) );
    arm_me();
    set_default_answer(this_object()->short() 
        + " looks at you and goes bark, bark, bark!");
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
    MONEY_MAKE( random(2), "gold")->move(TO);
    MONEY_MAKE( 3 + random(4), "silver")->move(TO);

    clone_object(WEAPON + "battle_axe")->move(TO);
    clone_object(ARMOUR + "ragged_fur")->move(TO);
    clone_object(DOORS + "storeroom_key")->move(TO);    

    command("wear all");
    command("wield all");
    return;
}
