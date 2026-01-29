inherit "/std/receptacle";
#include "/sys/stdproperties.h"
/* by Antharanos */
void
create_receptacle()
{
    set_name("bag");
    set_adj("large");
    add_adj("leather");
    set_long("A large container made of tanned leather, it looks capable "+
      "of holding several items.\n");
    add_prop(CONT_I_WEIGHT, 1000);
    add_prop(CONT_I_MAX_WEIGHT, 101000);
    add_prop(CONT_I_VOLUME, 15000);
    add_prop(CONT_I_MAX_VOLUME, 115000);
    add_prop(OBJ_I_VALUE, 360);
    add_prop(OBJ_M_NO_SELL,1);
}
