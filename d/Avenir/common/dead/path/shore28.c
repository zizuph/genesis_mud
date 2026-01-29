// file name: shore28
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
   shore_long("The path turns again here, heading "
             +"northeast and south. West and north "
             +"lies the dismal moors, and the "
             +"dark sea extends out to the southeast."); 

   shore_exit("northeast","29");
   shore_exit("south","27");
   shore_marsh("west","55");
   shore_marsh("north","57");

   reset_room();
}

void
reset_room()
{
   shore_reset();
}
