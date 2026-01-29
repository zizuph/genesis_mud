/* wine.c:  Drink for Red Eye Inn. */

inherit "/std/drink";

#include "/sys/stdproperties.h"

create_drink() {
   set_name("wine");
   set_pname("wines");
   set_adj("khand");
   set_short("glass of wine from Khand");
   set_pshort("glasses of wine from Khand");
   set_long(break_string(
      "A glass of wine from Khand, dark red, very sweet. \n", 75));
   add_prop(OBJ_I_VALUE, 0);
   set_soft_amount(120);
   set_alco_amount(20);
   add_prop(OBJ_I_WEIGHT,120);
   add_prop(OBJ_I_VOLUME,120);
}
