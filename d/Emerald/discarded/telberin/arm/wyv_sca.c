inherit "/std/armour";

#include "default.h"

void
create_armour()
{
   set_name("scale");
   set_short("wyvern scale");
   set_long("This slightly dented scale is from a wyvern, not as strong as " +
            "it's close relation: a dragon.\n");
   set_adj("wyvern");
   
   set_ac(14);
   set_at(A_SHIELD);
   /*    impale  slash   bludgeon   */
   set_am(({2, 0,-2 }));
   add_prop(OBJ_I_VALUE, 589);
   add_prop(OBJ_I_WEIGHT, 1709);
   add_prop(OBJ_I_VOLUME, 991);
}
