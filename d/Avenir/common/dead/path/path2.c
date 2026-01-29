// file name: path2
// creator: Ilyian, September 20, 1995
// last update:
// purpose: A path along the marshes in ~Avenir/common/dead/
// note: most of the code in these rooms is inherited in
//       ~avenir/common/dead/dead.c
// bug(s):
// to_do:

inherit "/d/Avenir/common/dead/dead.c";
#include "../dead.h"

void
create_room()
{
   path_long("On either side of the path stretches "
            +"out a desolate marsh, covered with fog. The "
            +"path continues to the north, and to the south "
            +"there appears to be a crossroads."); 
   AI(({"crossroads","crossroad"}),"To the south there "
            +"seems to be crossing of the roads.\n");

   path_exit("north","3");
   AE(PATH+"cross","south",0,1);
   path_marsh("west","1");
   path_marsh("east","54");

   path_reset();
}
