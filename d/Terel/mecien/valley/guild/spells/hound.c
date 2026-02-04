/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/creature";
inherit "/std/combat/unarmed";

#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>

#define TO            this_object()
#define TP            this_player()

#define A_BITE  0
#define A_CLAW  1

#define H_HEAD  0
#define H_BODY  1
#define H_LEGS  2

public void
create_creature()
{
    ::create_creature();
    
    set_name("wolf");
    set_long(
   "A beautiful and noble hound, its coat a file silvery white fur, " +
   "with bluish eyes that sparkle like stars.\n"
    );
    set_adj(({"mysterious", "silvery-white"}));
    set_race_name("hound");

    set_stats(({ 90, 90, 90, 50, 50, 100 }));
    set_learn_pref( ({10,10,10,10,10,10}) );
    set_hp(9999);
    set_mana(9999);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_SEE_DARK, 1);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME,  100000);
    add_prop(CONT_I_MAX_WEIGHT, 140000);
    add_prop(CONT_I_MAX_VOLUME, 140000);
    add_prop(LIVE_I_QUICKNESS, 80);
    set_skill(SS_DEFENCE,      40);
    set_skill(SS_PARRY,      45);
    set_skill(SS_AWARENESS,    60);
    set_skill(SS_UNARM_COMBAT, 50);
    set_skill(SS_CLIMB,        60);
    set_skill(SS_LOC_SENSE,    90);
    set_skill(SS_HUNTING,      90);

    add_item(({"teeth"}), "The teeth are sharp.\n");
    add_item(({"fur"}), "The fur is beautiful, silvery-white in colour.\n");
}

public void
cr_configure()
{
    add_attack(65, 60, W_IMPALE, 70, A_BITE);
    add_attack(35, 27, W_SLASH,  30, A_CLAW);

    add_hitloc( ({ 20, 20, 20 }), 25, "head",  H_HEAD);
    add_hitloc( ({ 32, 32, 32 }), 45, "body",  H_BODY);
    add_hitloc( ({ 32, 32, 32 }), 30, "legs",  H_LEGS);
}

public string
cr_attack_desc(int aid)
{
    switch (aid) {
      case A_BITE:return "teeth";
      case A_CLAW:return "claw";
    }
}
