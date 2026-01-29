/*
 *   f_pie.c:  Food for the Hobbiton bakery.
 */

#pragma save_binary

inherit "/std/food";

#include "/sys/stdproperties.h"

create_food() {
   set_name("pie");
   set_adj("apple");
   set_short("apple pie");
   set_pshort("apple pies");
   set_long(break_string(
      "The apple pie smells just like the ones your grandma used to "
    + "bake for you when you were a little child.\n",70));

   add_prop(OBJ_I_VALUE, 5);
   set_amount(5*5);
   add_prop(OBJ_I_WEIGHT,90);
   add_prop(OBJ_I_VOLUME,92);
}