// file name: shore18
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
   shore_long("The path turns sharply from the southwest "
             +"to the north here, following a bend in the "
             +"shoreline of the island. Dark waves splash "
             +"against the rocks to the west, and to "
             +"the north and south lies the grey fens."); 

   shore_exit("southwest","17");
   shore_exit("north","19");
   shore_marsh("east","46");
   shore_marsh("south","45");

   reset_room();
}

void
reset_room()
{
   shore_reset();
}
