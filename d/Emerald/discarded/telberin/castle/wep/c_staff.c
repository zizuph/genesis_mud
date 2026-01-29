inherit "/std/weapon";

#include "default.h"
#include <formulas.h>
void
create_weapon()
{
    set_name("staff");
    set_short("clerical staff");
    set_long("This is a fine clerical staff, used mainly for religious " +
             "ceremonies.\n");
    set_adj("clerical");

    set_default_weapon(12, 12, W_POLEARM, W_BLUDGEON,  
         W_BOTH,  0);
    add_prop(OBJ_I_WEIGHT, 659); 
    add_prop(OBJ_I_VOLUME,  400); 
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(12, 12) + random(30) - 40);
}
