// file name: shore14
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
   shore_long("The path continues to head straight "
             +"north and south here. Some fog from the "
             +"moors to the east is rolling slowly "
             +"across the path and into the black "
             +"water to the west."); 

   shore_exit("north","15");
   shore_exit("south","13");
   shore_marsh("east","37");

   reset_room();
}

void
reset_room()
{
   shore_reset();
}
