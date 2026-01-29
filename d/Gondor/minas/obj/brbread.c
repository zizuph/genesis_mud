/*
 *   brbread.c:  Food for the Minas Tirith bakery.
 */

inherit "/std/food";

#include "/sys/stdproperties.h"

create_food() {
   set_name("bread");
   set_adj("brown");
   set_short("piece of brown bread");
   set_pshort("pieces of brown bread");
   set_long(break_string(
      "This is a normal piece of brown bread, and it looks quite newly "
    + "baked. In fact, it looks quite tempting to eat.\n",70));

   add_prop(OBJ_I_VALUE, 9);
   set_amount(125);
   add_prop(OBJ_I_WEIGHT,100);
   add_prop(OBJ_I_VOLUME,154);
}
