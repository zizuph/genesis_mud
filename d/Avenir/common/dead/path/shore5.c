// file name: shore5
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
   shore_long("The path heads straight to the "
             +"northwest and the southeast, following "
             +"along the shoreline. To the north and "
             +"east you can see the oppressing grey "
             +"fog of the moors."); 

   shore_exit("northwest","6");
   shore_exit("southeast","4");
   shore_marsh("east","4");
   shore_marsh("north","5");

   reset_room();
}

void
reset_room()
{
   shore_reset();
}
