// file name: shore20
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
   shore_long("The path bends from the east to the "
             +"southwest here, dividing the marsh "
             +"to the south from the dark sea to "
             +"the north."); 

   shore_exit("east","21");
   shore_exit("southwest","19");
   shore_marsh("south","50");

   reset_room();
}

void
reset_room()
{
   shore_reset();
}
