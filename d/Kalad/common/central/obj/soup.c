inherit "/std/food";
#include "/d/Kalad/defs.h"
#include "/sys/stdproperties.h"
/* by Korat */
void
create_food()
{
   set_name("soup");
   set_adj("disgusting");
   set_short("disgusting soup");
   set_long("The disgusting smell from this soup wafts into "+
      "your nose, making your stomack twist.\n");
   set_amount(500);
   add_prop(OBJ_I_WEIGHT,500);
   add_prop(OBJ_I_VOLUME,750);
   add_prop(OBJ_I_VALUE,150);
}
