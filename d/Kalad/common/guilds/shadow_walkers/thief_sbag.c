inherit "/std/receptacle";
#include "/sys/stdproperties.h"

/* by Sarrr */

void
create_receptacle()
{
   set_name("bag");
   set_adj("small");
   add_adj("black");
   add_adj("leather");
   set_short("small black leather bag");
   set_long("A small container made of tanned leather, it looks capable "+
      "of holding a few items. It is dyed black.\n");
   add_prop(CONT_I_WEIGHT, 200);
   add_prop(CONT_I_MAX_WEIGHT, 9000);
   add_prop(CONT_I_VOLUME, 1000);
   add_prop(CONT_I_MAX_VOLUME, 12000);
   add_prop(OBJ_I_VALUE, 260);
   add_prop(OBJ_M_NO_SELL,1);
}
