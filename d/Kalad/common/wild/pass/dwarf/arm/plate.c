inherit "/d/Kalad/std/armour.c";
#include "/d/Kalad/defs.h"
/* by korat */
create_armour()
{
   ::create_armour();
   set_name("platemail");
  set_adj("bulky");
   set_long("This platemail was not forged to be used by dwarves, "+
      "but rather for humans. And this must have been done years ago "+
      "since the plates shows signs of heavy use.\n");
   set_ac(20);
   set_at(A_TORSO | A_ARMS);
   add_prop(OBJ_I_VALUE, 500);
   add_prop(OBJ_I_VOLUME, 4000);
   add_prop(OBJ_I_WEIGHT, 4000);
}
