// file name: shore4
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
   shore_long("The island makes a sharp bend here, and "
             +"the path follows it, turning from the "
             +"east to the northwest. Just off the "
             +"path to the north are the grey moors."); 

   shore_exit("east","3");
   shore_exit("northwest","5");
   shore_marsh("north","4");

   reset_room();
}

void
reset_room()
{
   shore_reset();
}
