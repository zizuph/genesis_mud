// file name: shore2
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
   shore_long("A grim marsh lies to the north and west, while "
             +"the shore path continues along to the "
             +"southwest and east. The dark sea to the "
             +"south is silent."); 

   shore_exit("southwest","3");
   shore_exit("east","1");
   shore_marsh("north","2");
   shore_marsh("west","3");

   reset_room();
}

void
reset_room()
{
   shore_reset();
}
