inherit "/std/torch";
#include <stdproperties.h>
void
create_torch()
{
   set_name("stove");
   set_adj("black");
   set_long("A large, black stove that is used to cook food on.\n");
   set_strength(1);
   set_short("black stove");
    add_prop(OBJ_I_WEIGHT, 250000);
   add_prop(OBJ_I_VOLUME, 50000);
   add_prop(OBJ_M_NO_GET,"Its just too heavy! You give up getting "+
      "the stove.\n");
   set_time(1000);
}

