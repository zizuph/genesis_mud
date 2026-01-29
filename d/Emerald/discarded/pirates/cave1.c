inherit "/std/room";
#include "defs.h"

void
create_room()
{
   set_short("A cave.");
   set_long(break_string(
         "This room is very hot. Steam covers the ground. "+
         "There is no obvious reason for all this steam. It must be rising "+
         "from somewhere beneath the floor.\n",74));
   add_item(({"ground","floor"}),break_string(
         "The floor is very hot and covered with steam. Although you "+
         "can see nothing on the ground through the steam, "+
         "you assume there must be some kind of vent for an "+
         "underground heat source here.\n"
         ,74));
   add_item(({"wall","walls"}),
      "The walls are very hot and damp to the touch.\n");
   
   add_prop(ROOM_I_INSIDE, 1);
   add_exit(THIS_DIR+"boardroom","east",0);
}
