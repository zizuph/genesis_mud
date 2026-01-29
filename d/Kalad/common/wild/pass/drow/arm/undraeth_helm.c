inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
#include <wa_types.h>
/* by Antharanos */
create_armour()
{
   ::create_armour();
   set_name("helm");
   set_adj("black");
   add_adj("adamantine");
   set_long("An open-faced helmet of delicate yet strong adamantine "+
      "metal. It has been crafted with maximum protection coupled with "+
      "maximum comfort in mind.\n");
   set_ac(20);
   set_at(A_HEAD);
   add_prop(OBJ_I_VALUE, 500);
   add_prop(OBJ_I_WEIGHT,2500);
   add_prop(OBJ_I_VOLUME,2500);
}
