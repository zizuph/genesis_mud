inherit "/std/armour";

#include "default.h"

void
create_armour()
{
   set_name("helmet");
   set_short("brigandine helmet");
   set_long("This helmet is made of a treated leather with metal plates " +
            "overlapping it all over.\n");
   set_adj("brigandine");
   
   set_ac(14);
   set_at(A_HEAD);
   /*    impale  slash   bludgeon   */
   set_am(({ -1, -1, 2 }));
   add_prop(OBJ_I_VALUE, 195);
   add_prop(OBJ_I_WEIGHT, 612);
   add_prop(OBJ_I_VOLUME, 410);
}
