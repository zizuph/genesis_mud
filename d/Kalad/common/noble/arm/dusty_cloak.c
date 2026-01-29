inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* SARR */

void
create_armour()
{
    ::create_armour();
    set_name("cloak");
    set_adj("dusty");
    set_short("dusty cloak");
    set_long("This cloak looks old. It is covered with dust from the road.\n");
    set_ac(3);
    set_at(A_ROBE);
    add_prop(OBJ_I_WEIGHT,500);
    add_prop(OBJ_I_VOLUME,400);
}

