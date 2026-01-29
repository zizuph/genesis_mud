// file name: shore19
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
   shore_long("The path turns again here, bearing "
             +"northeast and south. The fog on the "
             +"downs to the east is grey and impenetrable."); 

   shore_exit("northeast","20");
   shore_exit("south","18");
   shore_marsh("east","50");

   reset_room();
}

void
reset_room()
{
   shore_reset();
}
