inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
#include "/sys/stdproperties.h"
/* by Antharanos */
create_armour()
{
    ::create_armour();
    set_name("armour");
    set_adj("hardened");
    add_adj("leather");
    set_long("A suit of leather armour that has been boiled and hardened to the "+
      "point that it affords protection similar to that of lesser metal "+
      "armours. Upon the front is an image of a dark sun.\n");
    set_ac(14);
    set_at(A_BODY);
    add_prop(OBJ_I_VALUE,500);
    add_prop(OBJ_I_VOLUME,2200);
    add_prop(OBJ_I_WEIGHT,2200);
}
