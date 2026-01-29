inherit "/std/food";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_food()
{
   set_name("steak");
   set_adj("juicy");
   set_short("juicy steak");
   set_pshort("juicy steaks");
   set_long("A succulent and exquisitely tender grilled steak.\n");
   add_prop(OBJ_I_WEIGHT,275);
   add_prop(OBJ_I_VOLUME,275);
   set_amount(275);
}
