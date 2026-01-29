/*
 *   f_cake.c:  Food for the Hobbiton bakery.
 */

#pragma save_binary

inherit "/std/food";

#include "/sys/stdproperties.h"

create_food() {
   set_name("cake");
   set_adj("strawberry");
   set_short("strawberry cake");
   set_pshort("strawberry cakes");
   set_long(break_string(
      "The strawberry cake smell delicious! You cannot wait to put your "
    + "teeth in the light-brown piece of food.\n",70));

   add_prop(OBJ_I_VALUE, 12);
   set_amount(12*12);
   add_prop(OBJ_I_WEIGHT,70);
   add_prop(OBJ_I_VOLUME,76);
}