/*
 * lboots.c
 *
 * A pair of leather boots to be sold in Dol Amroth.
 *
 * By Skippern 20(c)01
 */
inherit "/std/armour";

#include <formulas.h>
#include <stdproperties.h>
#include <wa_types.h>

private nomask void
create_armour()
{
    set_name("boots");
    add_adj("leather");
    set_short("pair of leather boots");
    set_pshort("pairs of leather boots");
    set_long("This is a pair of leather boots. They are made for " +
	     "walking, but gives some protection aswell.\n");

    set_looseness(0);

    set_at(A_FEET);
    set_ac(2);
    set_am(({ 0, 0, -2 }));

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(2, A_FEET));
    add_prop(OBJ_I_VOLUME, F_WEIGHT_DEFAULT_ARMOUR(2, A_FEET) / 5);
    set_af(this_object());
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(2) + 100);

}
