// file name: shore11
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
   shore_long("The grey marshes to the east and the "
             +"north are covered in a misty grey "
             +"haze. The path continues to skirt "
             +"between the shoreline and the swamp, "
             +"heading northwest and south."); 

   shore_exit("northwest","12");
   shore_exit("south","10");
   shore_marsh("east","25");
   shore_marsh("north","29");

   reset_room();
}

void
reset_room()
{
   shore_reset();
}
