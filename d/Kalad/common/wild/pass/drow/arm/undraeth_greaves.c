inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
#include <wa_types.h>
/* by Antharanos */
create_armour()
{
   ::create_armour();
   set_name("greaves");
   set_adj("black");
   add_adj("adamantine");
   set_long("A pair of leg armours crafted from midnight-black adamantine "+
      "metal, the most impervious substance known to exist. The armour "+
      "combines both strength and beauty to create an armour like none other "+
      "before.\n");
   set_ac(19);
   set_at(A_LEGS);
   add_prop(OBJ_I_VALUE, 400);
   add_prop(OBJ_I_WEIGHT,7500);
   add_prop(OBJ_I_VOLUME,7500);
}
