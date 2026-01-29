// file name: shore15
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
   shore_long("The path bends from the south to the "
             +"northeast, following the irregular shape "
             +"of the island. The the east, the misty "
             +"swamp looms."); 

   shore_exit("south","14");
   shore_exit("northeast","16");
   shore_marsh("east","40");

   reset_room();
}

void
reset_room()
{
   shore_reset();
}
