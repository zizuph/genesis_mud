// file name: shore17
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
   shore_long("The path continues northeast and southwest "
             +"here. The grey moors lie to the east and "
             +"south."); 

   shore_exit("northeast","18");
   shore_exit("southwest","16");
   shore_marsh("south","43");
   shore_marsh("east","45");

   reset_room();
}

void
reset_room()
{
   shore_reset();
}
