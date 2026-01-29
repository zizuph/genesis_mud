/*
 *   f_cake.c:  Food for the Hobbiton bakery.
 */

inherit "/std/food";

#include "/sys/stdproperties.h"

create_food() {
   set_name("salt");
   add_name("pinch");
  add_name("spice");
   set_adj("pinch");
  set_adj("of");
  set_short("pinch of salt");
  set_pshort("pinches of salt");
   set_long(break_string(
    "A small pinch of salt. It might just be sufficient to flavor a single dish.\n",70));
   add_prop(OBJ_I_VALUE, 0);
  set_amount(1);
   add_prop(OBJ_I_WEIGHT,5);
   add_prop(OBJ_I_VOLUME,1);
}
