/*
 *   /d/Gondor/ithilien/poros/armour/breastplate.c
 *
 *   This is the body armour worn by the corsair Captain while at the base.
 *
 *   Talisan,  Febuary 1996
 * Modification log:
 * Gwyneth - Added more verbose set_pshort 4/1/01
 */

#pragma strict_types

inherit "/std/armour";
inherit "/lib/keep";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_armour()
{
    set_name(({"breastplate", "plate armour", "plate"}));
    set_short("black high-steel breastplate");
    set_pshort("black high-steel breastplates");
    set_long("This pure black plate armour has been expertly crafted "
      + "in Umbar, from the finest of steels found in all of Harad. On "
      + "the breastplate, is the crested image of a great winged drake.\n");
    set_adj(({"black", "high-steel", "high steel", "umbarim", "steel"}));

    set_default_armour(40, A_BODY,({-2,4,-2}), 0);

    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(40) + random(250) - 150);
    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(40,A_BODY)+random(1000)-1000);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
}
