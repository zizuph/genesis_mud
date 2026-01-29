inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
#include <wa_types.h>
/* by Antharanos */
create_armour()
{
   ::create_armour();
   set_name("belt");
   set_adj("ruby-studded");
   add_adj("leather");
   set_long("A large belt fashioned from leather with small rubies "+
      "embedded along its length.\n");
   set_ac(7);
   set_at(A_WAIST);
   add_prop(OBJ_I_VALUE,1200);
   add_prop(OBJ_I_WEIGHT,600);
   add_prop(OBJ_I_VOLUME,600);
}
