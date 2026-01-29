inherit "/d/Kalad/std/armour";
#include <wa_types.h>
#include "/d/Kalad/defs.h"

void
create_armour()
{
   set_name("cloak");
   set_adj("brown");
   set_long("This is a brown cloak made in Kabal.\n");
   add_prop(OBJ_I_VALUE, 30);
   add_name("_kalad_clothes_shop_");
   set_default_armour(2,A_ROBE, 0, 0);
}
