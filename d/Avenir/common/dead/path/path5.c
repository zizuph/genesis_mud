// file name: path5
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
   path_long("The path continues to the north, where it "
       +"seems to be ascending slightly, and back to the "
       +"southeast. The fog that lies on the marshes to the "
       +"west and east is grey and impenetrable."); 

   path_exit("north","6");
   path_exit("southeast","4");
   path_marsh("west","21");
   path_marsh("east","58");

   path_reset();




}
