/*
 *   pie.c:  Food for the Minas Tirith bakery.
 */

inherit "/std/food";

#include "/sys/stdproperties.h"

create_food() {
   set_name("pie");
   set_adj("fruit");
   set_short("fruit pie");
   set_pshort("fruit pies");
   set_long(break_string(
      "The fruit pie smells of exciting Gondorian fruits "
    + " brought in from different places in the land.\n",70));
   add_prop(OBJ_I_VALUE, 5);
  set_amount(50);
   add_prop(OBJ_I_WEIGHT,45);
   add_prop(OBJ_I_VOLUME,70);
}
