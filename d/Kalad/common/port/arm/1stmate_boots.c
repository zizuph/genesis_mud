inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
#include "/sys/stdproperties.h"
/* by Antharanos */
create_armour()
{
    ::create_armour();
    set_name("boots");
    set_adj("hardened");
    add_adj("leather");
    set_long("A tough-looking pair of boots made entirely of hardened leather. "+
      "Although hardened for protection on the exterior, the interior of "+
      "the boots is lined with soft brown fur, offering some measure of "+
      "comfort as well as protection.\n");
    set_ac(12);
    set_at(A_FEET);
    add_prop(OBJ_I_VALUE,480);
    add_prop(OBJ_I_VOLUME,1400);
    add_prop(OBJ_I_WEIGHT,1400);
}
