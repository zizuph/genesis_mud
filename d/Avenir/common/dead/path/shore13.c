// file name: shore13
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
   shore_long("The path runs straight north and south, "
             +"dividing the fog-stained marshes to the "
             +"east from the dark sea to the west."); 

   shore_exit("south","12");
   shore_exit("north","14");
   shore_marsh("east","34");

   reset_room();
}

void
reset_room()
{
   shore_reset();
}
