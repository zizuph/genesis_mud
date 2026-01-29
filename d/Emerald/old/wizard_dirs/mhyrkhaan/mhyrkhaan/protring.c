inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"

void
create_armour()
{
   ::create_armour();
   set_name("ring");
   set_adj("steel");
   add_adj("plain");
   set_short("plain steel ring");
   set_long("This ring is made from a plain, flat band of steel.\n");
   set_at(A_ANY_FINGER);
   set_ac(2);
   add_prop(OBJ_I_WEIGHT,25);
   add_prop(OBJ_I_VOLUME,4);
   add_prop(OBJ_I_VALUE,100);
}
