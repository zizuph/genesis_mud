/*
 *   f_cake.c:  Food for the Hobbiton bakery.
 */

inherit "/std/food";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"

create_food() {
   set_name("egg");
   add_adj(({"brown"}));
   add_name("_cookie_egg_");
  set_short("brown egg");
  set_pshort("brown eggs");
   set_long(break_string(
    "The "+query_short()+" looks quite fresh and "+
    "wholesome.\n",70));
   add_prop(OBJ_I_VALUE, 0);
  set_amount(15);
   add_prop(OBJ_I_WEIGHT,160);
   add_prop(OBJ_I_VOLUME,105);
}
