/*
 *   /d/Gondor/ithilien/poros/armours/chainmail.c
 *
 *   This is the armour worn by the Dunadan traveler, who is encamped
 *   atop the hill, along the path near the Poros river.
 *
 *   Talisan,  February 1996
 * Modification log:
 * Gwyneth - Added more verbose set_pshort 4/1/01
 */

#pragma strict_types

inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_armour()
{
    set_name(({"chainmail", "chainmail armour", "armour", "armor"}));
    set_short("grey chainmail");
    set_pshort("grey chainmails");
    set_long("This grey, high steel chainmail is finely crafted Gondorian "
      + "armour. It offers good protection for the upper body "
      + "and arms.\n");
    set_adj(({"gondorian", "grey", "high steel", "high-steel"}));

set_default_armour(28,A_BODY|A_ARMS,({0,0,0}), 0);

    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(28)+random(300));
    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(28,A_BODY)-random(400));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
}
