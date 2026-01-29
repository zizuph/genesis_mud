/*
 *   cake.c:  Food for the Minas Tirith bakery.
 */

inherit "/std/food";

#include "/sys/stdproperties.h"

create_food() {
   set_name("cake");
   set_adj("strawberry");
   set_short("strawberry cake");
   set_pshort("strawberry cakes");
   set_long(break_string(
      "The cake smells delicious! You can't wait to put your "
    + "teeth in this cake with Gondorian strawberries.\n",70));
   add_prop(OBJ_I_VALUE, 12);
  set_amount(175);
   add_prop(OBJ_I_WEIGHT,175);
   add_prop(OBJ_I_VOLUME,200);
}
