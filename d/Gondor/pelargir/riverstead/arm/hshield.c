/*
 * This file is NCAMP_ARM + "hshield.c"
 */
#pragma strict_types

inherit "/std/armour.c";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

public void
create_armour()
{
    set_name("shield");
    set_pname("shields");
    set_short("round wooden shield");
    set_pshort("round wooden shields");
    set_adj("round");
    add_adj("wooden");
    set_long("This round wooden shield appears to have been fashioned by someone "
        + "more skilled in woodworking and carpentry than armour-making. It would "
        + "still protect you better than nothing.\n");
    set_default_armour(8, A_SHIELD, ({ -2, 1, 1, }), 0);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR( 8, A_SHIELD) + random(501));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(8) + random(25));
}
