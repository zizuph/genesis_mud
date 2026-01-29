inherit "/d/Kalad/std/armour";

#include "/d/Kalad/defs.h"


void
create_armour()
{
    ::create_armour();
    set_name("tunic");
    set_adj("leather");
    set_long("A leather tunic.\n");
    set_at(A_TORSO);
    set_ac(15);
}

