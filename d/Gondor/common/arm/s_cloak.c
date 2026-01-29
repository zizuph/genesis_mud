/*
 * /d/Gondor/common/arm/s_cloak.c
 *
 * This cloak is worn by the surgeon.
 *
 * /Mercade, 4 May 1993
 *
 * Revision history:
 */

inherit "/std/armour";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Gondor/defs.h"

#define ARMOUR_CLASS 8

void
create_armour()
{
    set_name("mantle");
    add_name("cloak");

    set_pname("mantles");
    add_pname("cloaks");

    set_adj("smooth");
    add_adj("wool");

    set_short("smooth mantle");
    set_pshort("smooth mantles");

    set_long(BSN("This mantle is made of wool. It is woven very smoothly " +
        "which makes it very comfortable."));

    set_ac(ARMOUR_CLASS);
    set_at(A_ROBE);
    set_am( ({ 1, 1, -2 }) );

    add_prop(OBJ_I_WEIGHT, 1300);
    add_prop(OBJ_I_VOLUME, 1300);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS) + random(151) - 75);
}
