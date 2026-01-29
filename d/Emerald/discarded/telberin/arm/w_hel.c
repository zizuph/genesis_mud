inherit "/std/armour";

#include "default.h"

void
create_armour()
{
   set_name("helmet");
   set_short("white helmet");
   set_long("This white helmet is a leather covered metal cap, whose " +
            "leather has been starched white.\n");
   set_adj("white");
   
   set_ac(18);
   set_at(A_HEAD);
   /*    impale  slash   bludgeon   */
   set_am(({  1,     1,   -2 }));
   add_prop(OBJ_I_VALUE, 265);
   add_prop(OBJ_I_WEIGHT, 301);
   add_prop(OBJ_I_VOLUME, 245);
}
