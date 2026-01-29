#include "default.h"

inherit CASTLE_ROOM;

void
create_room()
{
   set_short("drop room");
   set_long("The walls here have tattered tapestries on them, the colours "+
      "faded by time spent in a dry atmosphere. There is a "+
      "passage leading east and south. To the east you can see "+
      "something on the ground.\n");

   add_exit(CASTLE_DIR + "3k3","north");
   add_exit(CASTLE_DIR + "3k10","south");
   
   add_item(({"tapestries","tapestry"}), "The tapestries depict scenes "+
      "from ancient battles, they are\nextremely faded now "+
      "due to the atmosphere.\n");
   
}
