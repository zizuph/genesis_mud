inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
#include <wa_types.h>
create_armour()
{
   ::create_armour();
   set_name("gauntlets");
   set_adj("black");
   add_adj("adamantine");
   set_long("A luxuriously wrought pair of night-black adamantine "+
      "gauntlets. Their design combines both beauty and strength to form the "+
      "near perfect armour.\n");
   set_ac(19);
   set_at(A_ARMS);
   add_prop(OBJ_I_VALUE, 300);
   add_prop(OBJ_I_WEIGHT,5000);
   add_prop(OBJ_I_VOLUME,5000);
}
