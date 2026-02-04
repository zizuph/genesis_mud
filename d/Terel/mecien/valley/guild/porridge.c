/* Creative rights reserved to Mecien(Jeff Babcock) and team. */

inherit "/std/food";
#include <stdproperties.h>

create_food()
{
   set_name("porridge");
   set_adj("sweet");
   set_long("A thick porridge of oats and wheat. It has been sweetened\n"
      + "with honey, raisins and cinnamon.\n");
   set_amount(63);
   add_prop(OBJ_I_WEIGHT, 80);
   add_prop(OBJ_I_VOLUME, 60);
}
