// file name: shore30
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
   shore_long("The path heads straight to the north and "
             +"south here, dividing the dark sea "
             +"to the east and the mist shrouded mire "
             +"to the west."); 

   shore_exit("north","31");
   shore_exit("south","29");
   shore_marsh("west","60");

   reset_room();
}

void
reset_room()
{
   shore_reset();
}
