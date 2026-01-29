/* 
 * Standard Haradrim vest from Harondor.
 * Serif, July 2001.
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
    set_name(({"vest", "leather vest", "armour", "armor",
        "leather armour", "leather armor", "black vest", "black armour",
        "black leather vest", "black leather armour", "black leather armor"}));
    set_short("black leather vest");
    set_pshort("black leather vests");
    set_long("This vest is crafted of fine leather from Harad, dyed black "
        + "and embroidered with golden thread. It offers some protection for "
        + "the upper body.\n");
    set_adj(({"leather", "black", "haradrim", "dyed"}));

    set_default_armour(22,A_BODY,({0,0,0}), 0);

    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(28)+random(150));
    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(28,A_BODY)-random(100));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
}
