/*
 *   f_cake.c:  Food for the Hobbiton bakery.
 */

inherit "/std/food";

#include "/sys/stdproperties.h"

create_food() {
   set_name("porridge");
  add_name("bowl");
   set_adj("hot");
   set_short("bowl of hot porridge");
   set_pshort("bowls of hot porridge");
   set_long(break_string(
      "The hot porridge smells nice and wholesome, and you figure it will "
    + "be a nice little meal for you.\n",70));
   add_prop(OBJ_I_VALUE, 0);
  set_amount(55);
   add_prop(OBJ_I_WEIGHT,80);
   add_prop(OBJ_I_VOLUME,76);
}
