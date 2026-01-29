/*
 *   f_cake.c:  Food for the Hobbiton bakery.
 */

inherit "/std/food";

#include "/sys/stdproperties.h"

create_food() {
   set_name("honey");
   add_name("gob");
   add_name("_cookie_honey_");
   set_adj("hot");
  set_short("gob of honey");
  set_pshort("gobs of honey");
   set_long(break_string(
    "The "+query_short()+" looks quite sweet and "+
    "gooey.\n",70));
   add_prop(OBJ_I_VALUE, 0);
  set_amount(15);
   add_prop(OBJ_I_WEIGHT,160);
   add_prop(OBJ_I_VOLUME,105);
}
