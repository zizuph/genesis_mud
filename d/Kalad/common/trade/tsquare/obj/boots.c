
inherit "/d/Kalad/std/armour";
#include "/sys/stdproperties.h"
#include <wa_types.h>
#include "/d/Kalad/defs.h"

void
create_armour()
{
   set_name("boots");
   set_adj("leather");
   set_pshort("leather boots");
   set_long("This is a nice pair of boots made in Kabal.\n");
   add_prop(OBJ_I_VALUE, 30);
   add_name("_kalad_clothes_shop_");
   set_default_armour(2,A_FEET, 0, 0);
}
