/* Creative rights reserved to Mecien(Jeff Babcock) and team. */

inherit "/std/food";
#include <stdproperties.h>

create_food()
{
   set_name("cheese");
   set_adj("goat");
   set_long("A small round of fresh goat cheese.\n");
   set_amount(30);
   add_prop(OBJ_I_WEIGHT, 40);
   add_prop(OBJ_I_VOLUME, 30);
}
