inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
#include "/sys/stdproperties.h"
/* by Antharanos */
create_armour()
{
    ::create_armour();
    set_name("boots");
    set_adj("tough");
    add_adj("leather");
    set_long("A tough-looking pair of boots made entirely of hardened leather. "+
      "They don't look particularly comfortable, but then again, a seaman's "+
      "life isn't one of luxury.\n");
    set_ac(10);
    set_at(A_FEET);
    add_prop(OBJ_I_VALUE,400);
    add_prop(OBJ_I_VOLUME,1200);
    add_prop(OBJ_I_WEIGHT,1200);
}
