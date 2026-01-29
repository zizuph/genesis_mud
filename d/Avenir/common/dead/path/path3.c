// file name: path3
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
   path_long("The path continues to the north and the "
            +"south, dividing up a grim moor on either "
            +"side of it."); 

   path_exit("north","4");
   path_exit("south","2");
   path_marsh("west","12");
   path_marsh("east","55");

   path_reset();
}
