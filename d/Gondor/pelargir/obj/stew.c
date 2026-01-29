/*
 *   f_cake.c:  Food for the Hobbiton bakery.
 */

inherit "/std/food";

#include "/sys/stdproperties.h"

create_food() {
   set_name("stew");
  add_name("bowl");
   set_adj("fish");
   set_short("bowl of hot fish stew");
   set_pshort("bowls of hot fish stew");
   set_long(break_string(
    "The fish stew looks really delicious, at least for those who love "+
    "fish, with green and red vegetable pieces stewed "+
    "together with some kind of white fish, and cooked en masse.\n",70));
   add_prop(OBJ_I_VALUE, 0);
  set_amount(100);
   add_prop(OBJ_I_WEIGHT,120);
   add_prop(OBJ_I_VOLUME,96);
}
