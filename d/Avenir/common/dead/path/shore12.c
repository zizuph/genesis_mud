// file name: shore12
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
   shore_long("The path continues north as far as you "
             +"can see, and bends back to the southest "
             +"along a natural inlet. The grim and "
             +"dismal swamp to the east emanates a "
             +"feeling of depression and fear."); 

   shore_exit("southeast","11");
   shore_exit("north","13");
   shore_marsh("east","29");

   reset_room();
}

void
reset_room()
{
   shore_reset();
}
