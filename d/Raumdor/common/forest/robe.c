inherit "/d/Raumdor/std/armour";
#include "/d/Raumdor/defs.h"

/* SARR */

void
create_armour()
{
    ::create_armour();
    set_name("robe");
    add_adj("tattered");
    set_long("This is an old, grey tattered robe. There is dried "+
    "blood on it.\n");
    set_ac(2);
    set_at(A_ROBE);
    add_prop(OBJ_I_VALUE,1);
    add_prop(OBJ_I_WEIGHT,500);
    add_prop(OBJ_I_VOLUME,350);
}

