/*
 *   f_cake.c:  Food for the Hobbiton bakery.
 */

inherit "/std/food";

#include "/sys/stdproperties.h"

create_food() {
   set_name("bacon");
   add_name("plate");
  add_name("beans");
   set_adj("hot");
  set_short("hot plate of beans and bacon");
  set_pshort("hot plates of beans and bacon");
   set_long(break_string(
    "The hot plate of beans and bacon smells so delicious that you "+
    "feel like eating it right away.\n",70));
   add_prop(OBJ_I_VALUE, 0);
  set_amount(70);
   add_prop(OBJ_I_WEIGHT,70);
   add_prop(OBJ_I_VOLUME,76);
}
