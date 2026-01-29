inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
create_armour()
{
   ::create_armour();
   set_name("armour");
   set_adj("plain");
   set_long("A plain set of armour.\n");
   set_ac(15);
   set_at(A_BODY);
   add_prop(OBJ_I_WEIGHT,7500);
   add_prop(OBJ_I_VOLUME,7500);
   add_prop(OBJ_I_VALUE,100);
}
