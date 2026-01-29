inherit "/std/food";
#include <stdproperties.h>
#include "/d/Shire/common/defs.h"

void
create_food()
{
   set_name("pie");
   add_name("_bumbleberry_pie_");
   add_adj(({"fresh","bumbleberry"}));
   set_short("fresh bumbleberry pie");
   set_long("This fresh bumbleberry pie looks as if it has "+
   "been just taken from the oven.  It looks yummy!\n");

   set_amount(200);
   add_prop(OBJ_I_WEIGHT, 200);
   add_prop(OBJ_I_VALUE, 0);
   add_prop(OBJ_I_VOLUME, 400);
   add_prop("_i_am_bumbleberry_pie_",1);

}
