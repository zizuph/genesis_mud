inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
#include "/sys/stdproperties.h"
/* by Antharanos */
create_armour()
{
    ::create_armour();
    set_name("hat");
    set_adj("expensive-looking");
    add_adj("plumed");
    set_long("An extravagantly decorated hat. Upon it are a myriad number of tiny "+
      "gemstones and feathers from exotic love-birds.\n");
    set_ac(5);
    set_am(({-5,-5,5}));
    set_at(A_HEAD);
    add_prop(OBJ_I_VALUE,500);
    add_prop(OBJ_I_VOLUME,800);
    add_prop(OBJ_I_WEIGHT,800);
}
