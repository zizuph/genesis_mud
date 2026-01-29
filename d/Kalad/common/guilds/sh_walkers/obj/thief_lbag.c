inherit "/std/receptacle";
#include "/sys/stdproperties.h"

/* by Sarrr */

void
create_receptacle()
{
   set_name("bag");
   set_adj("large");
   add_adj("black");
   add_adj("leather");
   set_short("large black leather bag");
   set_long("A large container made of tanned leather, it looks capable "+
      "of holding several items. It is dyed black.\n");
   add_prop(CONT_I_WEIGHT, 600);
   add_prop(CONT_I_MAX_WEIGHT, 101000);
   add_prop(CONT_I_VOLUME, 15000);
   add_prop(CONT_I_MAX_VOLUME, 115000);
   add_prop(OBJ_I_VALUE, 360);
   add_prop(OBJ_M_NO_SELL,1);
}
