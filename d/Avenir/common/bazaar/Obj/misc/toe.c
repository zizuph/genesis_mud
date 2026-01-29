// toe of newt
// cut from the corpse of a newt
// add ingredients prop.

inherit "/std/leftover";
#include "/d/Avenir/common/common.h"
 
void
create_leftover()
{
   set_name("toe");
   add_adj("e");
   add_name("avenir_toe_newt");
   set_short("toe of newt");
   set_long("This is the toe of a newt. This and other viscera "+
       "are purported to be ingredients for potions and whatnot.\n");
   set_decay_time(10);
   add_prop(OBJ_I_WEIGHT, 5);
   add_prop(OBJ_I_VOLUME, 9);
}
