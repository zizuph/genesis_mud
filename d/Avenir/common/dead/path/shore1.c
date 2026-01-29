// file name: shore1
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
   shore_long("The path continues to the west, while back "
             +"to the east there appears to be a "
             +"crossroads. To the north is a dismal "
             +"swamp."); 
   AI(({"crossroads","crossroad"}),"It appears to be a place "
             +"where an east-west path intersects with a "
             +"north-south one.\n");

   AE(PATH+"cross","east",0,1);
   shore_exit("west","2");
   shore_marsh("north","1");

   reset_room();
}

void
reset_room()
{
   shore_reset();
}
