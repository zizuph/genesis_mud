/* whiskey.c:  Drink for Red Eye Inn. */

inherit "/std/drink";

#include "/sys/stdproperties.h"

create_drink() {
   set_name("whiskey");
   set_pname("whiskeys");
   set_adj("mirkwood");
   set_short("glass of whiskey from Mirkwood");
   set_pshort("glasses of whiskey from Mirkwood");
   set_long(break_string(
      "A glass of whiskey from the souther eaves of Mirkwood, "
    + "where easterlings from the inland Sea of Rhun live as thralls "
    + "of the Dark Lord under the shadow of Dol Guldur. \n", 75));
   add_prop(OBJ_I_VALUE, 0);
   set_soft_amount(120);
   set_alco_amount(40);
   add_prop(OBJ_I_WEIGHT,120);
   add_prop(OBJ_I_VOLUME,120);
}
