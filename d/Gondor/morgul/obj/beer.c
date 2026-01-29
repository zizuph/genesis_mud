/* beer.c:  Drink for Red Eye Inn. */

inherit "/std/drink";

#include "/sys/stdproperties.h"

create_drink() {
   set_name("beer");
   set_pname("beers");
   set_adj("Red Eye");
   set_short("mug of Red Eye Beer");
   set_pshort("mugs of Red Eye Beer");
   set_long(break_string(
      "A mug of Red Eye Beer, a strong dark beer with a bitter taste. \n", 75));
   add_prop(OBJ_I_VALUE, 0);
   set_soft_amount(270);
   set_alco_amount(8);
   add_prop(OBJ_I_WEIGHT,270);
   add_prop(OBJ_I_VOLUME,270);
}
