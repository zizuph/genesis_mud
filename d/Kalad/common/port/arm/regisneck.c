inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
#include "/sys/stdproperties.h"
/* by Antharanos */
create_armour()
{
    ::create_armour();
    set_name("brooch");
    set_adj("golden");
    set_long("A gold-chain brooch with many intricate filigree carvings "+
      "on its surface.\n");
    set_ac(12);
    set_at(A_NECK);
    add_prop(OBJ_I_VALUE,960);
    add_prop(OBJ_I_VOLUME,750);
    add_prop(OBJ_I_WEIGHT,750);
}
