// file name: path4
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
   path_long("The path twists slightly, bearing to the "
            +"northwest and to the south. The desolate "
            +"marshes lie on either side of the path."); 

   path_exit("northwest","5");
   path_exit("south","3");
   path_marsh("west","17");
   path_marsh("east","56");

   path_reset();
}
