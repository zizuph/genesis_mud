// file name: shore9
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
   shore_long("The path turns from the south to the "
             +"northeast here, following the contour of "
             +"the island. The moors lie to the east, "
             +"exuding a feeling of hollow depression."); 

   shore_exit("northeast","10");
   shore_exit("south","8");
   shore_marsh("east","18");

   reset_room();
}

void
reset_room()
{
   shore_reset();
}
