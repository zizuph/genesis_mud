// file name: shore29
// creator: Ilyian, September 21, 1995
// last update: room along the Shore path around the
//              Isle of the Dead
// purpose:
// note: Most of the code for this room is contained
//       in the inherited file /d/Avenir/common/dead/dead.c
// bug(s):
// to_do:

inherit "/d/Avenir/common/dead/dead.c";
#include "../dead.h"

void
create_room()
{
   shore_long("The path heads to the north and southwest "
             +"here, following along the contour of the "
             +"island. The fog-stained swamp lies to "
             +"the west."); 

   shore_exit("north","30");
   shore_exit("southwest","28");
   shore_marsh("west","57");

   reset_room();
}

void
reset_room()
{
   shore_reset();
}
