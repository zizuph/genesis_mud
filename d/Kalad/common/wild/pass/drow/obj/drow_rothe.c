inherit "/std/food";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_food()
{
   set_name("rothe");
   set_adj("tender");
   add_adj("juicy");
   set_short("tender juicy rothe");
   set_pshort("tender juicy rothe");
   set_long("A succulent and indredibly tender slab of grilled rothe "+
      "meat.\n");
   add_prop(OBJ_I_WEIGHT,250);
   add_prop(OBJ_I_VOLUME,250);
   set_amount(250);
}
