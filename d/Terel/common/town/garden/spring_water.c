inherit "/std/drink";
#include <stdproperties.h>

create_drink()
{
   set_name("water");
   set_adj("spring");
   add_name("spring water");
   set_long("Crystal clear spring water.\n");
   set_soft_amount(50);
   add_prop(OBJ_I_WEIGHT, 50);
   add_prop(OBJ_I_VOLUME, 50);
}
