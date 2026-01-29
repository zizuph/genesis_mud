inherit "/std/food";
#include "/d/Kalad/defs.h"
#include "/sys/stdproperties.h"
/* by Korat */
void
create_food()
{
   set_name("bread");
   set_adj("fresh-baked");
   set_short("fresh-baked bread");
   set_long("A delicious fresh-baked bread.\n");


   add_prop(OBJ_I_WEIGHT,250);
   add_prop(OBJ_I_VOLUME,250);
   add_prop(OBJ_I_VALUE,50);
}
