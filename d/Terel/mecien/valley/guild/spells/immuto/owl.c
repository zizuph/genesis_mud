/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
/*
 *  A mystic owl. Mortricia 930310
 *                Modified to inherit immuto_animal 960110
 */

inherit "/d/Terel/mecien/valley/guild/spells/immuto/immuto_animal";

#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>

#define A_BITE  0
#define A_CLAW  1

#define H_HEAD  0
#define H_BODY  1
#define H_LEGS  2
#define H_WINGS 3

public string
query_m_out()
{
    return "flies away";
}

public string
query_m_in()
{
    return "flies in.";
}

public void
create_creature()
{
    ::create_creature();
    
    set_name("owl");
    set_short("grey owl");
    set_long("It's a grey owl. It looks, however, " +
             "somewhat mysterious.\n");
    set_adj("grey");
    set_race_name("owl");

    set_stats( ({15,15,15,25,25,25}) );
    set_learn_pref( ({10,10,10,10,10,10}) );
    set_hp(9999);
    set_mana(9999);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_SEE_DARK, 1);
    add_prop(LIVE_I_SEE_INVIS, 1);
    add_prop(CONT_I_WEIGHT, 5000);
    add_prop(CONT_I_VOLUME,  4000);
    add_prop(CONT_I_MAX_WEIGHT, 8000);
    add_prop(CONT_I_MAX_VOLUME, 6000);
    add_prop(LIVE_I_QUICKNESS, 95);
    set_skill(SS_DEFENCE,      40);
    set_skill(SS_AWARENESS,    50);
    set_skill(SS_UNARM_COMBAT, 15);
    set_skill(SS_CLIMB,        99);
    set_skill(SS_LOC_SENSE,    90);
    set_skill(SS_HUNTING,      35);

    add_item(({"claws"}), "The claws are sharp.\n");
    add_item(({"feathers"}), "The feathers are in good shape.\n");
}

public void
cr_configure()
{
    add_attack(12, 12, W_IMPALE, 25, A_BITE);
    add_attack(18, 18, W_SLASH,  75, A_CLAW);

    add_hitloc( ({ 5, 5, 5 }), 25, "head",  H_HEAD);
    add_hitloc( ({ 9, 9, 9 }), 45, "body",  H_BODY);
    add_hitloc( ({ 9, 9, 9 }), 10, "legs",  H_LEGS);
    add_hitloc( ({ 5, 5, 5 }), 20, "wings", H_WINGS);
}

public string
cr_attack_desc(int aid)
{
    switch (aid) {
      case A_BITE:return "beak";
      case A_CLAW:return "claws";
    }
}
