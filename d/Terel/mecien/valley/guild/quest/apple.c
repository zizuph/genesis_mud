/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/food";
#include <stdproperties.h>

create_food()
{
   set_name("apple");
   set_short("red apple");
   set_adj("red");
   set_long("It's a beautiful bright red apple, it looks delicious.\n");
   set_amount(10);
   add_name("mystic_quest_apple");
   add_prop(OBJ_I_VALUE, 1);
}
