// file name: shore3
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
   shore_long("Some grey mist is floating down from "
             +"the swamps to the north. The path follows "
             +"the shoreline to the northeast and west."); 

   shore_exit("west","4");
   shore_exit("northeast","2");
   shore_marsh("north","3");

   reset_room();
}

void
reset_room()
{
   shore_reset();
}
