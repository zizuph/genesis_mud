inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* SARR */

void
create_armour()
{
    ::create_armour();
    set_name("tunic");
    set_adj("torn");
    set_short("torn tunic");
    set_long("This is a very dirty tunic that is torn and tattered.\n");
    set_ac(1);
    set_at(A_TORSO);
    add_prop(OBJ_I_WEIGHT,100);
    add_prop(OBJ_I_VOLUME,80);
}

