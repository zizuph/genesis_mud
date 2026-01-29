inherit "/d/Kalad/std/armour.c";
#include "/d/Kalad/defs.h"
/* by korat */
create_armour()
{
   ::create_armour();
   set_name("shield");
   set_adj("battered");
   set_long("This shield has seen better days, but will "+
      "still give some protection when you fight.\n");
   set_ac(10);
   set_at(A_SHIELD);
   add_prop(OBJ_I_VALUE, 200);
   add_prop(OBJ_I_VOLUME,1000);
   add_prop(OBJ_I_WEIGHT,2000);
}
