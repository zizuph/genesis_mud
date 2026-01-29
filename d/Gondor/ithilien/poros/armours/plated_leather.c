/*
 *   /d/Gondor/ithilien/poros/armours/plated_leather.c
 *
 *   This is the armour worn by the corsair 1st mate at the base.
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
    set_name(({"leather armour", "plated armour"}));
    set_short("plated leather armour");
    set_pshort("plated leather armours");
    set_long("This black leather armour has been reinforced with steel "
      + "plates that cover the vital areas of the upper body. The armour "
      + "has been recently polished, and is well maintained.\n");
    set_adj(({"black", "plated", "polished"}));

    set_default_armour(25,A_BODY,({-1,2,-1}), 0);

    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(25)+random(400));
    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(25,A_BODY)+random(250));
   add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
}
