/*
 *   whbread.c:  Food for the Minas Tirith bakery.
 */

inherit "/std/food";

#include "/sys/stdproperties.h"

create_food() {
   set_name("bread");
   set_adj("white");
   set_short("piece of white bread");
   set_pshort("pieces of white bread");
   set_long(break_string(
      "This is a normal piece of white bread, and it does not look "
    + "too old to eat yet.\n",70));

   add_prop(OBJ_I_VALUE, 6);
   set_amount(100);
   add_prop(OBJ_I_WEIGHT,100);
   add_prop(OBJ_I_VOLUME,154);
}









