// eye of eel
// cut from the corpse of an eel
// add ingredients prop.

inherit "/std/leftover";
#include "/d/Avenir/common/common.h"
 
void
create_leftover()
{
   set_name("eye");
   add_adj("eel");
   add_name("avenir_eel_eye");
   set_short("eye of eel");
   set_long("This is the eye of an eel. This and other viscera "+
       "are purported to be ingredients for potions and whatnot.\n");
   set_decay_time(10);
   add_prop(OBJ_I_WEIGHT, 5);
   add_prop(OBJ_I_VOLUME, 9);
}
