// file name: path7
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
   path_long("The path continues to the north, and slightly "
            +"downhill to the southwest. The marshes lie "
            +"east and west."); 

   path_exit("north","8");
   path_exit("southwest","6");
   path_marsh("west","28");
   path_marsh("east","64");

   path_reset();
}
