inherit "/std/drink";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_drink()
{
   set_soft_amount(125);
   set_alco_amount(10);
   set_name("beer");
   set_adj("dwarfish");
   set_short("dwarfish beer");
   set_pshort("dwarfish beers");
   set_long("A dark brew made by local dwarves.\n");
   add_prop(OBJ_I_WEIGHT,125);
   add_prop(OBJ_I_VOLUME,125);
}
