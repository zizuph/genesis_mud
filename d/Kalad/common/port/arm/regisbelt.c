inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
#include "/sys/stdproperties.h"
/* by Antharanos */
create_armour()
{
    ::create_armour();
    set_name("belt");
    set_adj("gold-buckled");
    set_long("A leather belt complete with a golden buckle.\n");
    set_ac(10);
    set_am(({-5,-5,5}));
    set_at(A_WAIST);
    add_prop(OBJ_I_VALUE,500);
    add_prop(OBJ_I_VOLUME,900);
    add_prop(OBJ_I_WEIGHT,900);
}
