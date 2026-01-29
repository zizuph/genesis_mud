/*
 *   f_cake.c:  Food for the Hobbiton bakery.
 */

inherit "/std/food";

#include "/sys/stdproperties.h"

create_food() {
   set_name("stew");
  add_name("bowl");
   set_adj("vegetable");
   set_short("bowl of hot vegetable stew");
   set_pshort("bowls of hot vegetable stew");
   set_long(break_string(
    "The vegetable stew looks really delicious (for those who love "+
    "vegetables), with green and red vegetable pieces stewed "+
    "together and cooked en masse.\n",70));
   add_prop(OBJ_I_VALUE, 0);
  set_amount(50);
   add_prop(OBJ_I_WEIGHT,70);
   add_prop(OBJ_I_VOLUME,76);
}
