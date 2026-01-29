/*
 * /d/Gondor/common/arm/s_mask.c
 *
 * This mask is worn by the surgeon. It does not make someone invisible.
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

#define ARMOUR_CLASS 4

void
create_armour()
{
    set_name("mask");

    set_pname("masks");

    set_adj("surgeons");
    add_adj("white");

    set_short("surgeons mask");
    set_pshort("surgeons masks");

    set_long(BSN("It is a typical surgeons mask. It is white. It is used " +
	"by surgeons to mask them while performing surgery on someone to " +
	"make sure they are not recognized in case something goes wrong."));

    set_ac(ARMOUR_CLASS);
    set_at(A_HEAD);
    set_am( ({ 0, 0, 0 }) );

    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VOLUME, 300);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS) + random(51) - 25);
}
