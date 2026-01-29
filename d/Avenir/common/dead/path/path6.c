// file name: path6
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
   path_long("The path turns again here, bearing slightly "
            +"uphill to the northeast. The fog-stained "
            +"moors lie to the west and the east, and "
            +"seem to encroach on the path with their "
            +"ominous mystery."); 

   path_exit("northeast","7");
   path_exit("south","5");
   path_marsh("west","24");
   path_marsh("east","61");

   path_reset();
}
