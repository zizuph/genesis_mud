inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_armour()
{
   ::create_armour();
   set_name("shield");
   set_adj("old");
   add_adj("steel");
   set_long("A triangular shield of steel that bears the faded mark of "+
      "a dark sun upon it.\n");
   set_ac(15);
   set_at(A_SHIELD);
   add_prop(OBJ_I_VALUE,180);
   add_prop(OBJ_I_VOLUME,2500);
   add_prop(OBJ_I_WEIGHT,2500);
}
