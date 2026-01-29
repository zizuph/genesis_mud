inherit "/std/receptacle";
#include "/d/Kalad/defs.h"
/* by Antharanos */
void
create_receptacle()
{
    set_name("box");
    set_adj("large");
    add_adj("bronze");
    set_long("A large container fashioned from shiny bronze. If you wished "+
      "to, you could probably drop off some items here, so that less "+
      "fortunate individuals could gain their benefit.\n");
    add_prop(CONT_I_WEIGHT,20000);
    add_prop(CONT_I_MAX_WEIGHT,220000);
    add_prop(CONT_I_VOLUME,20000);
    add_prop(CONT_I_MAX_VOLUME,220000);
    add_prop(OBJ_I_VALUE,1000);
    add_prop(OBJ_M_NO_GET,"The large bronze box is firmly stuck to the "+
      "ground. You fail in your attempt to remove it.\n");
}
