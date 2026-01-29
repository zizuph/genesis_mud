/* d_ale.c:  Drink for Red Eye Inn. */

inherit "/std/drink";

#include "/sys/stdproperties.h"

create_drink() {
   set_name("ale");
   set_pname("ales");
   set_adj("morgul");
   set_short("glass of Morgul Vale Ale");
   set_pshort("glasses of Morgul Vale Ale");
   set_long(break_string(
      "Morgul Vale Ale looks and tastes as if it water right out "
    + "of stinking Morgulduin. But they probably put in some dirt "
    + "to improve colour and flavour. \n", 75));

   add_prop(OBJ_I_VALUE, 0);
   set_soft_amount(90);
   set_alco_amount(3);
   add_prop(OBJ_I_WEIGHT,90);
   add_prop(OBJ_I_VOLUME,90);
}
