
// Ledge path 6 (/d/Avenir/common/ledge/ledge6.c)
// creator(s): Ilyian
// last update:  
// purpose:
//
// note:
// bug(s):
// to-do:

inherit "/d/Avenir/common/ledge/std_ledge";
#include "ledge.h"

void
create_room()
{
     AE(LEDGE+"ledge5", "northwest", 0, 6);
     AE(LEDGE+"ledge7", "south", 0, 0);

   SHORT("On the steep path");
   make_the_room("  The path heads down to the south, and curves "
       +"up to the northwest. You are about halfway along the "
       +"ledge now. You can see a faint light to the north, and "
       +"far to the south is a dark tunnel entrance.\n");

     AI(("tunnel"),"You can make out no features of the tunnel "
       +"from this distance.\n");

}

