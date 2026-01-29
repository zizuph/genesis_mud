/*  f_cake.c:  Food for the Hobbiton bakery.  */

inherit "/std/food";

#include "/sys/stdproperties.h"

create_food() {
   set_name("porridge");
   add_name("bowl");
   set_adj("warm");
   set_short("bowl of warm porridge");
    set_pname("bowls");
    add_pname("porridges");
   set_pshort("bowls of warm porridge");
   set_long(break_string(
      "It is some grey, pappy substance, smelling of mould and old "
    + "dishes. It definitely has not been made from oatmeal, but you "
    + "do not want to know what it has been made from. \n", 75));
   add_prop(OBJ_I_VALUE, 0);
   set_amount(55);
   add_prop(OBJ_I_WEIGHT,70);
   add_prop(OBJ_I_VOLUME,76);
}

