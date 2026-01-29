inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* Silk tux, by Sarr */
void
create_armour()
{
    ::create_armour();
    set_name("tuxedo");
    set_adj("silk");
    add_adj("black");
    add_prop(OBJ_I_WEIGHT,1000);
    add_prop(OBJ_I_VOLUME,800);
    add_prop(OBJ_I_VALUE,200);
    set_ac(8);
    set_at(A_BODY);
}

