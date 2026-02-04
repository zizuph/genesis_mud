/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
/*
 *  A mystic cricket Mortricia 930310
 *                   Modified to inherit immuto_animal 960110
 */

inherit "/d/Terel/mecien/valley/guild/spells/immuto/immuto_animal";

#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>

#define A_BITE  0

#define H_BODY  0

public void
create_creature()
{
    ::create_creature();
    
    set_name("cricket");
    set_short("tiny cricket");
    set_long("It's a tiny cricket. It looks, however, " +
             "somewhat mysterious.\n");
    set_adj("tiny");
    set_race_name("insect");

    set_stats( ({2,2,2,3,3,2}) );
    set_learn_pref( ({10,10,10,10,10,10}) );
    set_hp(9999);
    set_mana(9999);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(OBJ_I_INVIS, 1);
    add_prop(CONT_I_WEIGHT, 1);
    add_prop(CONT_I_HEIGHT, 1);
    add_prop(CONT_I_VOLUME,  2);
    add_prop(CONT_I_MAX_WEIGHT, 2);
    add_prop(CONT_I_MAX_VOLUME, 4);
    add_prop(OBJ_M_NO_GET, 0);
    add_prop(CONT_I_IN, 0);
    set_skill(SS_DEFENCE,       2);
    set_skill(SS_AWARENESS,    10);
    set_skill(SS_UNARM_COMBAT,  2);
    set_skill(SS_CLIMB,        10);
    set_skill(SS_LOC_SENSE,    10);
    set_skill(SS_HUNTING,       2);

    add_item(({"legs"}), "The legs are... Can you really see them?\n");
}

public void
cr_configure()
{
    add_attack(1, 1, W_IMPALE, 100, A_BITE);

    add_hitloc( ({ 1, 1, 1 }), 100, "body",  H_BODY);
}

public string
cr_attack_desc(int aid)
{
    switch (aid) {
      case A_BITE:return "bite";
    }
}
