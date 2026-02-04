/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
/*
 *  A mystic bear. Mortricia 930310
 *                 Modified to inherit immuto_animal 960110
 */

inherit "/d/Terel/mecien/valley/guild/spells/immuto/immuto_animal";

#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>

#define A_BITE  0
#define A_LPAW  1
#define A_RPAW  2

#define H_HEAD  0
#define H_BODY  1
#define H_LEGS  2
#define H_PAWS  3

public void
create_creature()
{
    ::create_creature();
    
    set_name("bear");
    set_short("large brown bear");
    set_long("It's a bear. It looks, however, somewhat " +
             "mysterious.\n");
    set_adj(({"large", "brown"}));
    set_race_name("bear");

    set_stats( ({85,85,85,20,20,85}) );
    set_learn_pref( ({10,10,10,10,10,10}) );
    set_hp(9999);
    set_mana(9999);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(CONT_I_WEIGHT, 200000);
    add_prop(CONT_I_VOLUME,  200000);
    add_prop(CONT_I_MAX_WEIGHT, 280000);
    add_prop(CONT_I_MAX_VOLUME, 280000);
    add_prop(LIVE_I_QUICKNESS, 50);
    set_skill(SS_DEFENCE,      50);
    set_skill(SS_PARRY,        55);
    set_skill(SS_AWARENESS,    50);
    set_skill(SS_UNARM_COMBAT, 60);
    set_skill(SS_CLIMB,        50);
    set_skill(SS_LOC_SENSE,    50);
    set_skill(SS_HUNTING,      60);

    add_item(({"teeth"}), "The teeth are sharp.\n");
    add_item(({"fur"}), "The fur is in good shape.\n");
}

public void
cr_configure()
{
    add_attack(75, 45, W_IMPALE, 20, A_BITE);
    add_attack(63, 39, W_SLASH,  42, A_RPAW);
    add_attack(61, 37, W_SLASH,  38, A_LPAW);

    add_hitloc( ({ 25, 25, 25 }), 25, "head",  H_HEAD);
    add_hitloc( ({ 40, 40, 40 }), 45, "body",  H_BODY);
    add_hitloc( ({ 40, 40, 40 }), 10, "legs",  H_LEGS);
    add_hitloc( ({ 25, 25, 25 }), 20, "paws",  H_PAWS);
}

public string
cr_attack_desc(int aid)
{
    switch (aid) {
      case A_BITE:return "teeth";
      case A_RPAW:return "right paw";
      case A_LPAW:return "left paw";
    }
}
