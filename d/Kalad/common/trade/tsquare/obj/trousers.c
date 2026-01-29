inherit "/d/Kalad/std/armour";
#include "/sys/stdproperties.h"
#include <wa_types.h>
#include "/d/Kalad/defs.h"

void
create_armour()
{
   set_name("trousers");
   set_adj("rugged");
   set_pshort("rugged trousers");
   set_long("This is a nice pair of trousers made by Xavier.\n");
   add_prop(OBJ_I_VALUE, 30);
   add_name("_kalad_clothes_shop_");
   set_default_armour(2,A_LEGS, 0, 0);
}
