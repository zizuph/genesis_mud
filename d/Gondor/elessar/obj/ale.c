/*
 *   d_ale.c:  Drink for Brugan's Pub.
 */

inherit "/std/drink";

#include "/sys/stdproperties.h"

create_drink() {
   set_name("ale");
   set_pname("ales");
   set_adj("golden");
   set_short("glass of golden ale");
   set_pshort("glasses of golden ale");
   set_long(break_string(
      "The golden ale has a golden colour and smells like beer that "
    + "has been mixed with a lot of water.\n",70));

   add_prop(OBJ_I_VALUE, 0);
   set_soft_amount(90);      /* It is but a glass */
   set_alco_amount(1);        /* 2% alcohol        */
   add_prop(OBJ_I_WEIGHT,390);
   add_prop(OBJ_I_VOLUME,390);
}
