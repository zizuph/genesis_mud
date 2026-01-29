inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
#include <wa_types.h>
/* by Antharanos */
create_armour()
{
   ::create_armour();
   set_name("robe");
   set_adj("stygion-black");
   add_adj("silk");
   set_long("A long, voluminous robe fashioned from the softest of spider "+
      "silks. It seems to absorb the slightest of lights.\n");
   set_ac(1);
   set_at(A_ROBE);
   add_prop(OBJ_I_VALUE, 400);
   add_prop(OBJ_I_VOLUME,2000);
   add_prop(OBJ_I_WEIGHT,2000);
}
