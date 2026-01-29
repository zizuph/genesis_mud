/*
 * l_boots.c
 * Pair of leather boots, these are for Thanduin
 * - Alaron Feb 1998
 */

#include "../dirheader.h"
#include "../coramar.h"
#include <wa_types.h>
#include <formulas.h>
#include "/d/Emerald/defs.h"

inherit "/std/armour";

void
create_armour()
{
    set_name("boots");
    add_adj("leather");
    add_adj("pair");
    set_short("pair of leather boots");

    set_long("This is a pair of very well cared for leather boots. The "+
             "hide is soft and still fairly furry. How someone could have "+
             "kept the leather so supple in such a moist climate is amazing. "+
             "There aren't any special markings or decorations, but they "+
             "look like a useful pair of boots nonetheless.\n");

    set_at(A_FEET);
    set_ac(5);

    add_prop(OBJ_I_WEIGHT, 830);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(5));
}
