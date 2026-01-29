inherit "/std/armour";

#include "default.h"
#include <formulas.h>
void
create_armour()
{
        set_name("helmet");
        set_short("hard leather helmet");
        set_long("This helmet is made of a treated leather hide, and it " +
                 "appears to be as tough as metal.\n");
        set_adj("leather");
        add_adj("hard");

        set_ac(6);
        set_at(A_HEAD);
                /*    impale  slash   bludgeon   */
     set_am(({       0,      -1,    1 }));
        add_prop(OBJ_I_VALUE, 115);
        add_prop(OBJ_I_WEIGHT, 301);
        add_prop(OBJ_I_VOLUME, 245);
}
