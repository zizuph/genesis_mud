// file name: shore27
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
   shore_long("The path turns sharply from the "
             +"southwest to the north here, following "
             +"a bend in the shore of the island. The "
             +"grey marsh lies to the west, from which "
             +"a thick shroud of fog drifts."); 

   shore_exit("north","28");
   shore_exit("southwest","26");
   shore_marsh("west","54");

   reset_room();
}

void
reset_room()
{
   shore_reset();
}
