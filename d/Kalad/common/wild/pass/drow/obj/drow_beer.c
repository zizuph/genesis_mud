inherit "/std/drink";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_drink()
{
   set_soft_amount(100);
   set_alco_amount(8);
   set_name("beer");
   set_adj("fungus");
   set_short("fungus beer");
   set_pshort("fungus beers");
   set_long("A dark brew created by the mixture of a variety of unique "+
      "fungi found only within the Dark Dominion.\n");
   add_prop(OBJ_I_WEIGHT,100);
   add_prop(OBJ_I_VOLUME,100);
}
