inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* A dusty merchant's cloak, by Sarr */

create_armour()
{
    ::create_armour();
    set_name("cloak");
    set_adj("dusty");
    set_long(
        "This is a dusty cloak made of stiff leather.\n");
    set_ac(8);
    set_at(A_ROBE);
    add_prop(OBJ_I_WEIGHT,2400);
    add_prop(OBJ_I_VOLUME,2000);
    add_prop(OBJ_I_VALUE,150);
}
    
