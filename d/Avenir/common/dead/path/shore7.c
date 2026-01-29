// file name: shore7
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
   shore_long("The path heads straight for a while, leading "
             +"north and south. The swamps are to the east."); 

   shore_exit("north","8");
   shore_exit("south","6");
   shore_marsh("east","8");

   reset_room();
}

void
reset_room()
{
   shore_reset();
}
