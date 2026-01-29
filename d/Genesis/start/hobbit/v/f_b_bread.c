/*
 *   f_b_bread.c:  Food for the Hobbiton bakery.
 */

#pragma save_binary

inherit "/std/food";

#include "/sys/stdproperties.h"

create_food() {
   set_name("bread");
   set_adj("brown");
   set_short("piece of brown bread");
   set_pshort("pieces of brown bread");
   set_long(break_string(
      "This is a normal piece of brown bread, and it does not look "
    + "too old to eat yet. In fact, it looks healthy to you.\n",70));

   add_prop(OBJ_I_VALUE, 9);
   set_amount(9*9);
   add_prop(OBJ_I_WEIGHT,100);
   add_prop(OBJ_I_VOLUME,154);
}