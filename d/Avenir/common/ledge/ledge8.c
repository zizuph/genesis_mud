
// Ledge path 8 (/d/Avenir/common/ledge/ledge8.c)
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
     AE(LEDGE+"ledge7", "north", 0, 6);
     AE(LEDGE+"ledge9", "southeast", 0, 0);

   SHORT("On the steep path");
   make_the_room("  The path winds from the north to the southeast, "
      +"following along the cliff wall. Far down to the south you "
      +"see a dark tunnel entrance that leads into darkness.\n");


}

