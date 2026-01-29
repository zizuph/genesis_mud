inherit "/std/room";
#include "defs.h"

void
create_room()
{
   set_short("A cave.");
   set_long(
      "There is a little light coming from the west. "+
      "It gives you just enough light to see where "+
      "you are going. To the south it is very dark. "+
      "\n");
   add_item(({"ground","floor"}),
      "It is hard to see here, but the ground seems to "+
      "be made of wooden planks, rather than rock. "+
      "Someone went through an awful lot of work "+
      "to build this floor.\n"
   );
   add_item(({"wall","walls"}),
      "The walls are warm and damp to the touch.\n");
   
   add_prop(ROOM_I_INSIDE, 1);
   add_exit(THIS_DIR+"main","west",0);
   add_exit(THIS_DIR+"cave3","south",0);
}
