inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
#include "/sys/stdproperties.h"
/* by Antharanos */
create_armour()
{
    ::create_armour();
    set_name("gloves");
    set_adj("white");
    add_adj("silk");
    set_long("A nice pair of gloves made from some incredibly smooth silk, its "+
      "surface covered with delicately sewn images of beer mugs.\n");
    set_ac(5);
    set_at(A_HANDS);
    add_prop(OBJ_I_VALUE,500);
    add_prop(OBJ_I_VOLUME,400);
    add_prop(OBJ_I_WEIGHT,400);
}
