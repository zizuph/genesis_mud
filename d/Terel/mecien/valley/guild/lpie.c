/* Creative rights reserved to Mecien(Jeff Babcock) and team. */

inherit "/std/food";
#include <stdproperties.h>

create_food()
{
   set_name("pie");
   set_adj(({"roasted", "lamb"}));
  set_long("A golden brown pie of roasted lamb, with potatoes, " +
"onions, garlic and many herbs.\n");
   set_amount(700);
   add_prop(OBJ_I_WEIGHT, 220);
   add_prop(OBJ_I_VOLUME, 200);
}
