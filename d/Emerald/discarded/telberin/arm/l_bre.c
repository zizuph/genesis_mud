inherit "/std/armour";

#include "default.h"

void
create_armour()
{
   set_name("plate");
   add_name("breastplate");
   add_name("breast");
   add_adj("breat");
   add_adj("leather");
   set_short("leather breastplate");
   set_long("This leather breatplate has been cured in a strange liquid, " +
            "setting it as hard as wood.\n");
   
   set_ac(14);
   set_at(A_BODY);
   /*    impale  slash   bludgeon   */
   set_am(({       1,      1,      -2 }));
   add_prop(OBJ_I_VALUE, 340);
   add_prop(OBJ_I_WEIGHT, 657);
   add_prop(OBJ_I_VOLUME, 891);
}
