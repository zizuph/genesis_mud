// file name: path8
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
   path_long("The path bears northwest here, and continues "
            +"back to the south as well. You seem to be "
            +"slightly above the level of the moors now, "
            +"which lie to the east and west."); 

   path_exit("northwest","9");
   path_exit("south","7");
   path_marsh("west","33");
   path_marsh("east","66");

   path_reset();
}
