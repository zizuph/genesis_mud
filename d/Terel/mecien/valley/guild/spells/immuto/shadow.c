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

#define A_TOUCH  0

#define H_BODY  1

public void
create_creature()
{
    ::create_creature();
    
    set_name("shadow");
    set_adj(({"eerie", "ghostly"}));
    set_race_name("shadow");

    set_learn_pref( ({10,10,10,10,10,10}) );
    set_hp(9999);
    set_mana(9999);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_QUICKNESS, 50);
    set_skill(SS_DEFENCE,      100);
    set_skill(SS_PARRY,        55);
    set_skill(SS_AWARENESS,    100);
    set_skill(SS_UNARM_COMBAT, 60);
    set_skill(SS_CLIMB,        50);
    set_skill(SS_LOC_SENSE,    100);
    set_skill(SS_HUNTING,      60);
     add_prop(LIVE_I_SEE_DARK, 100);
   add_prop(LIVE_I_SEE_INVIS, 50);

    set_gender(2);
   add_prop(NPC_I_NO_LOOKS, 1);
}

public void
cr_configure()
{
    add_attack(20, 20, W_IMPALE, 20, A_TOUCH);

    add_hitloc( ({ 40, 40, 40 }), 45, "form",  H_BODY);
}

