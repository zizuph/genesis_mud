/*    Seaman attire
*     Amelia 3/8/98
*
*/

#pragma strict_types

inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>

#define ARMOUR_CLASS 12

public void
create_armour()
{
    set_name("jerkin");
    set_adj("leather");
    set_short("leather jerkin");
    set_long("A jerkin made from brown goat "+
        "leather. It is fairly tough and is designed to cover the "+
        "chest and shoulders like a jacket.\n");
    set_ac(ARMOUR_CLASS); 
    set_at(A_TORSO);
    set_am(({ -1, 2, -1 }));
    add_prop(OBJ_I_WEIGHT, 800);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS) + random(100));
}
