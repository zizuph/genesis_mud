inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* SARR */

void
create_armour()
{
    ::create_armour();
    set_name("shirt");
    set_adj("leather");
    set_short("leather shirt");
    set_long("A leather shirt with black studs.\n");
    set_ac(5);
    set_at(A_TORSO);
    add_prop(OBJ_I_WEIGHT,1000);
    add_prop(OBJ_I_VOLUME,900);
}

