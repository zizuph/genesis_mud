inherit "/d/Kalad/std/armour.c";
#include "/d/Kalad/defs.h"
/* by korat */
create_armour()
{
   ::create_armour();
   set_name("jerkin");
   set_adj("dirty");
  set_long("This jerkin seems to have been more used to "+
      "protect the last owner from food rather than swords. "+
      "It is all smeared with grease.\n");
   set_ac(10);
   set_at(A_TORSO | A_ARMS);
   add_prop(OBJ_I_VALUE, 200);
   add_prop(OBJ_I_VOLUME, 1000);
   add_prop(OBJ_I_WEIGHT, 1000);
}
