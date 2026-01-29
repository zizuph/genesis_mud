// file name: shore26
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
   shore_long("The path turns to the northeast here, and "
             +"back to the west you can see a crossroads. "
             +"The grey and dismal moors lie to the north, "
             +"and the waves of the dark sea lap against "
             +"the rocks to the south."); 
   AI(({"crossroads","crossroad"}),"It appears to be where "
             +"an east-west path intersects with a "
             +"north-south one.\n");

   shore_exit("northeast","27");
   AE(PATH+"cross","west",0,1);
   shore_marsh("north","54");

   reset_room();
}

void
reset_room()
{
   shore_reset();
}
