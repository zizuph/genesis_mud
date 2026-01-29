inherit "/std/food";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_food()
{
   set_name("fungus");
   set_adj("moldy");
   set_short("moldy fungus");
   set_pshort("moldy fungi");
   set_long("A rather disgusting-looking bit of fungus, it is however, "+
      "not unpleasant in its smell.\n");
   add_prop(OBJ_I_WEIGHT,50);
   add_prop(OBJ_I_VOLUME,50);
   set_amount(50);
}
