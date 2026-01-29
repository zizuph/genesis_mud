inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
#include "/sys/stdproperties.h"
/* by Antharanos */
create_armour()
{
    ::create_armour();
    set_name("robe");
    set_adj("extravagant");
    add_adj("blue");
    set_long("A silky-fine robe made from blue cloth. Gold filigree decorates "+
      "the robe's wrists and collar, as well as its hem.\n");
    set_ac(2);
    set_at(A_ROBE);
    add_prop(OBJ_I_VALUE,1000);
    add_prop(OBJ_I_VOLUME,1200);
    add_prop(OBJ_I_WEIGHT,1200);
}
