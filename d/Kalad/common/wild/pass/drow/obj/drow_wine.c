inherit "/std/drink";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_drink()
{
   set_soft_amount(300);
   set_alco_amount(25);
   set_name("wine");
   set_adj("dark");
   add_adj("purple");
   set_short("dark purple wine");
   set_pshort("dark purple wines");
   set_long("A wine whose color is the darkest shade of purple, so dark it "+
      "appears almost black.\n");
   add_prop(OBJ_I_WEIGHT,300);
   add_prop(OBJ_I_VOLUME,300);
}
