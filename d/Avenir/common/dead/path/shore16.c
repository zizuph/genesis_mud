// file name: shore16
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
   shore_long("The path heads straight from the northeast "
             +"to the southwest here, dividing the black "
             +"sea to the northwest from the ominous moors "
             +"to the south and east."); 

   shore_exit("northeast","17");
   shore_exit("southwest","15");
   shore_marsh("east","43");
   shore_marsh("south","40");

   reset_room();
}

void
reset_room()
{
   shore_reset();
}
