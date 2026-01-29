/*
 * This file is NCAMP_ARM + "hmail.c"
 */
#pragma strict_types

inherit "/std/armour.c";

#include <formulas.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Gondor/defs.h"


public void
create_armour() 
{
    set_name("chainmail");
    add_name("mail");
    set_short("ancient grey chainmail");
    set_pshort("ancient grey chainmails");
    set_long("This ancient grey chainmail is old-fashioned and "
        + "appears to be a souvenir of battles fought in times before memory. "
        + "It has been well-cared for, however, and would still provide a "
        + "reasonable amount of protection against the weapons of foes.\n");
    set_adj("ancient");
    set_adj("grey");
    set_default_armour(17, A_BODY, 0, 0);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(17, A_BODY) + random(1201));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 3);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(17) + random(101));
}
