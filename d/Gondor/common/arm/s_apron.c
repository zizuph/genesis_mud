/*
 * /d/Gondor/common/arm/s_apron.c
 *
 * This is the apron that is worn by the surgeon.
 *
 * /Mercade, 4 May 1994
 *
 * Revision history:
 */

inherit "/std/armour";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Gondor/defs.h"

#define ARMOUR_CLASS 2

void
create_armour()
{
    set_name("apron");
    set_pname("aprons");

    set_adj("white");
    add_adj("large");

    set_short("white apron");
    set_pshort("white aprons");

    set_long(BSN("It is a large white apron, worn by surgeons. It is still " +
	"clean, no blood stains can be seen on it."));

    set_ac(ARMOUR_CLASS);
    set_at(A_WAIST);
    set_am( ({ 0, 0, 0 }) );

    add_prop(OBJ_I_WEIGHT, 400);
    add_prop(OBJ_I_VOLUME, 400);
    add_prop(OBJ_I_VALUE,  F_VALUE_ARMOUR(ARMOUR_CLASS) + random(51) - 25);
}
