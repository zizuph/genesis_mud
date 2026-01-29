/*
 *   /d/Gondor/ithilien/poros/armours/studded_leather.c
 *
 *   This is the armour worn by the Haradan jailer at the corsair base.
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
    set_name(({"leather armour", "armour"}));
    set_short("studded leather armour");
    set_pshort("studded leather armours");
    set_long("This black leather armour has been reinforced with "
      + "steel studs that help give better protection. In certain "
      + "spots on the armour, traces of dried blood can be seen.\n");
    set_adj(({"studded", "black", "bloody"}));

    set_default_armour(17,A_BODY,({0,0,0}), 0);

    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(17)+random(200));
    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(17,A_BODY)+random(400));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
}
