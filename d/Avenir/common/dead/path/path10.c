// file name: path10
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
   path_long("The path rises steeply to the northeast, where "
            +"there seems to stand some sort of stone archway. "
            +"To the east and west, a rocky hillside slopes "
            +"down into the marshes below, and south the "
            +"path descends along the hill."); 
   AI(({"arch","archway","stone"}),"There appears to be "         
            +"a large stone arch looming over the path "
            +"to the northeast.\n");

   AE(PATH+"entry","northeast",0,1);
   path_exit("south","9");
   path_hill("west","2");
   path_hill("east","11");

   path_reset();
}
