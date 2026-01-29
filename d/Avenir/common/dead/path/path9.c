// file name: path9
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
   path_long("Below you you see the moors stretch out, and "
            +"directly to the east and west is a rocky "
            +"hillside that descends down into the swamps. The "
            +"path continues upwards to the north and back "
            +"down to the southeast."); 

   path_exit("north","10");
   path_exit("southeast","8");
   path_hill("west","1");
   path_hill("east","13");

   path_reset();
}
