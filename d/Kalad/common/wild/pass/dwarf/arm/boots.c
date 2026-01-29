inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_armour()
{
   ::create_armour();
   set_name("boots");
   set_adj("heavy");
   add_adj("dwarven");
   set_long("This pair of boots are very heavy but will protect your feet "+
      "against both the ground and other dangers. They are made to "+
      "be used both for warfare and mining, since they have small "+
      "metal plates attached to the hardened leather.\n");
   set_ac(19);
   set_at(A_FEET);
   add_prop(OBJ_I_VALUE,250);
   add_prop(OBJ_I_VOLUME,1500);
   add_prop(OBJ_I_WEIGHT,3000);
}
