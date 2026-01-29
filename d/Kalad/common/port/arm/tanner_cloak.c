inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
/* by Antharanos */
create_armour()
{
    ::create_armour();
    set_name("cloak");
    set_adj("large");
    add_adj("tanned");
    set_long("A nicely tanned leather cloak. Sewn onto it are the "+
      "following words:\n"+
      "Hand-made by Telbruin the Tanner.\n");
    set_ac(9);
    set_at(A_BODY);
    add_prop(OBJ_I_VALUE,54);
    add_prop(OBJ_I_VOLUME,4000);
    add_prop(OBJ_I_WEIGHT,4000);
}
