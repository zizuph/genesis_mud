/* -*- Mode: C -*-
 *
 * obj/arm/mage-robe.c
 *
 * Skippern 20(c)02
 *
 * The protecting robe of a mage, some extra protection compared to a 
 * normal robe, but nothing more.
 */
inherit "/std/armour";

#include <formulas.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#define ARM 6

void
create_armour()
{
    set_name("robe");
    set_adj("blue");
    set_short("blue robe");
    set_pshort("blue robes");
    set_long("This is a long blue robe with golden stars woven into the "+
	     "cloth.\n");

    set_default_armour(ARM, A_ROBE, (({ 0, 3, 1})), 0);

    add_prop(OBJ_I_WEIGHT, 550);
    add_prop(OBJ_I_VOLUME, 250);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARM) + random(20) - 5);
}
