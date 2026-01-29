// file name: shore8
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
   shore_long("The path continues to follow straight "
             +"along the shore of the island, heading "
             +"north and south. A soft cold breeze is "
             +"blowing off the marshes to the east."); 


   shore_exit("north","9");
   shore_exit("south","7");
   shore_marsh("east","13");

   reset_room();
}

void
reset_room()
{
   shore_reset();
}
