/*
 */

inherit "/std/food";
#include "/sys/stdproperties.h"

create_food() {
   set_name("ham");
   set_adj("piece of");
   set_adj("large");
   set_short("piece of ham");
    set_pshort("pieces of ham");
   set_long(break_string(
    "This large piece of ham looks delicious. The salty pork meat "+
    "would make a good, full meal for you.\n",75));
   add_prop(OBJ_I_VALUE, 0);
  set_amount(75);
   add_prop(OBJ_I_WEIGHT,175);
   add_prop(OBJ_I_VOLUME,200);
}
