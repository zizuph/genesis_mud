/*
 *   d_beer.c:  Drink for Brugan's Pub.
 */

inherit "/std/drink";

#include "/sys/stdproperties.h"

create_drink() {
   set_name(({"mug","beer"}));
   set_pname(({"mugs","beers"}));
   set_adj("prime");
   set_short("mug of prime beer");
   set_pshort("pints of prime beer");
   set_long(break_string(
      "The beer of the house is of prime quality. It was brewn in the "
    + "cellar of the inn.\n",70));

   add_prop(OBJ_I_VALUE, 0);
   set_soft_amount(110);      /* This is a pint */
   set_alco_amount(8);       /* 6% alcohol     */
   add_prop(OBJ_I_WEIGHT,540);
   add_prop(OBJ_I_VOLUME,540);
}
