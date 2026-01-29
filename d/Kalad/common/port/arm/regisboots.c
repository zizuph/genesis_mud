inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
#include "/sys/stdproperties.h"
/* by Antharanos */
create_armour()
{
    ::create_armour();
    set_name("boots");
    set_adj("soft");
    add_adj("leather");
    set_long("A wonderful pair of boots made from the softest dearskin "+
      "and topped by a silver buckle at the tip of each boot.\n");
    set_ac(7);
    set_am(({-5,-5,5}));
    set_at(A_FEET);
    add_prop(OBJ_I_VALUE,500);
    add_prop(OBJ_I_VOLUME,1100);
    add_prop(OBJ_I_WEIGHT,800);
}
