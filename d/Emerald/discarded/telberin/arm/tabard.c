inherit "/std/armour";

#include "stdproperties.h"
#include <formulas.h>
void
create_armour()
{
        set_name("tabard");
	set_name("_royal_tabard_");
        set_short("leather tabard");
        set_long("This is a tabard of the royal court of Telberin, the coat " +
                 "of arms clearly showing the prancing unicorn and the " +
                 "rampant griffon, set on a green field.\n");
        set_adj("leather");

        set_ac(10);
        set_at(A_TORSO);
                /*    impale  slash   bludgeon   */
        set_am(({       -1,      1,      0 }));
        add_prop(OBJ_I_VALUE, 240);
        add_prop(OBJ_I_WEIGHT, 670);
        add_prop(OBJ_I_VOLUME, 781);
}
