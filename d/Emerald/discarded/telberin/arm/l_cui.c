inherit "/std/armour";

#include "default.h"
#include <formulas.h>

void
create_armour()
{
    set_name("cuirasse");
    add_name("cuirasse");
    add_adj("leather");
        set_short("leather cuirasse");
        set_long("This cuirasse has been lovingly prepared and protects the " +
                 "neck against violence.\n");

        set_ac(10);
        set_at(A_NECK);
                /*    impale  slash   bludgeon   */
     set_am(({       0,      1,      -1 }));
        add_prop(OBJ_I_VALUE, 210);
        add_prop(OBJ_I_WEIGHT, 340);
        add_prop(OBJ_I_VOLUME, 330);
}
