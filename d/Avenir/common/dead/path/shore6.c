// file name: shore6
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
   shore_long("The path turns slightly from the southeast "
             +"to the north here, following a bend in the "
             +"island. The marshes lie to the east."); 

   shore_exit("north","7");
   shore_exit("southeast","5");
   shore_marsh("east","5");

   reset_room();
}

void
reset_room()
{
   shore_reset();
}
