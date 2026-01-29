/*
 */

inherit "/std/drink";

#include "/sys/stdproperties.h"

create_drink() {
   set_name("wine");
   set_name("wines");
   set_adj("white");
   set_short("bottle of white wine");
   set_pshort("bottles of white wine");
   set_long(break_string(
      "The sparkling white wine comes from the riped grapes "
    + "that were harvested in the land of Ithilien some years ago.\n",70));

   add_prop(OBJ_I_VALUE, 0);
   set_soft_amount(130);     /* This is a glass */
   set_alco_amount(24);      /* 15% alcohol     */
   add_prop(OBJ_I_WEIGHT,410);
   add_prop(OBJ_I_VOLUME,410);
}
