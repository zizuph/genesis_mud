/* Creative rights reserved to Mecien(Jeff Babcock) and team. */

inherit "/std/food";
#include <stdproperties.h>

create_food()
{
   set_name("fish");
   set_adj("salted");
  set_long("A large lake fish, smoked whole and cured with salt.\n");
   set_amount(350);
   add_prop(OBJ_I_WEIGHT, 100);
   add_prop(OBJ_I_VOLUME, 80);
}
