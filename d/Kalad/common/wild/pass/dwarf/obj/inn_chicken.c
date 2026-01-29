inherit "/std/food";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_food()
{
   set_name("chicken");
   set_adj("roast");
   set_short("roast chicken");
   set_pshort("roast chickens");
   set_long("A golden-brown chicken roasted to utter prefection, its "+
      "meat nice, tender and succulent.\n");
   add_prop(OBJ_I_WEIGHT,150);
   add_prop(OBJ_I_VOLUME,150);
   set_amount(150);
}
