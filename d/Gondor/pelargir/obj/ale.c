/*
 *  ale.c  - for the pub in Pelargir.
 */

inherit "/std/drink";

#include "/sys/stdproperties.h"

create_drink() {
   set_name("ale");
   set_pname("ales");
   set_adj("brown");
   set_short("mug of brown ale");
   set_pshort("mugs of brown ale");
   set_long(break_string(
      "The ale has a murky brown colour and smells like beer that "
    + "has not been brewed long enough, and then mixed with water.\n",70));

   add_prop(OBJ_I_VALUE, 0);
   set_soft_amount(100);      /* It is but a mug */
   set_alco_amount(2);        /* 2% alcohol        */
   set_drink_msg("The brown ale tasted a bit watery, but fairly good.\n");
   add_prop(OBJ_I_WEIGHT,390);
   add_prop(OBJ_I_VOLUME,390);
}
