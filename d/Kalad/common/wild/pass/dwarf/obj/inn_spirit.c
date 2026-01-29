inherit "/std/drink";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_drink()
{
   set_soft_amount(250);
   set_alco_amount(30);
   set_name("spirit");
   set_adj("dwarf");
   set_short("dwarf spirit");
   set_pshort("dwarf spirits");
   set_long("A strong brew made of potatoes. It looks a bit murky.\n");
   add_prop(OBJ_I_WEIGHT,250);
   add_prop(OBJ_I_VOLUME,250);
}
