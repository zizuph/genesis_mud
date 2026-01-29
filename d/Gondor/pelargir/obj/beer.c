/*
 *    beer.c   - for the Pelargir pub.
 */

inherit "/std/drink";

#include "/sys/stdproperties.h"

create_drink() {
   set_name("beer");
   add_name("mug");
   set_adj("prime");
   set_short("mug of prime beer");
   set_pshort("pints of prime beer");
   set_long(break_string(
      "The Pelargir beer is of prime quality. It was brewed in the "
    + "old town brewery last year.\n",70));

   add_prop(OBJ_I_VALUE, 0);
   set_soft_amount(120);      /* This is a pint */
   set_alco_amount(9);       /* 6% alcohol     */
   set_drink_msg("You enjoy every drop of this local beer.\n");
   add_prop(OBJ_I_WEIGHT,540);
   add_prop(OBJ_I_VOLUME,540);
}
