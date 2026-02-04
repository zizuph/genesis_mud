// Lilith Dec 2021: new apple to replace the 
//         mystic entrance quest from 30 years ago. 

inherit "/std/food";
#include <stdproperties.h>

void
create_food()
{
   set_name("apple");
   set_short("red apple");
   set_adj("red");
   add_adj(({"beautiful", "bright"}));
   set_long("It is a beautiful bright red apple. It looks delicious.\n");
   set_amount(10);
   add_prop(OBJ_I_VALUE, 10);
}
