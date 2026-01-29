inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_armour()
{
   ::create_armour();
   set_name("chainmail");
   set_adj("old");
   add_adj("steel");
   set_long("A suit of steel chainmail that is only beginning to show "+
      "the effects of the march of time, for it is quite dull and ragged in "+
      "appearance. A faded symbol of a dark sun is visible on it.\n");
   set_ac(23);
   set_at(A_BODY);
   add_prop(OBJ_I_VALUE,360);
   add_prop(OBJ_I_VOLUME,7500);
   add_prop(OBJ_I_WEIGHT,7500);
}
