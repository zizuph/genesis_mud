inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* SARR */

void
create_armour()
{
    ::create_armour();
    set_name("pants");
    set_adj("stained");
    set_short("stained pants");
    set_long("There are muddy pants with grass stains on them.\n");
    set_ac(2);
    set_at(A_LEGS);
    add_prop(OBJ_I_WEIGHT,250);
    add_prop(OBJ_I_VOLUME,200);
}

