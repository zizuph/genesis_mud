

// Ledge path 7 (/d/Avenir/common/ledge/ledge7.c)
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
     AE(LEDGE+"ledge6", "north", 0, 6);
     AE(LEDGE+"ledge8", "south", 0, 0);

   SHORT("On the steep path");
   make_the_room("  The path continues up to the north and down to "
      +"the south, and is very slippery. The cliff wall towers "
      +"high above you, and the dropoff below you falls an "
      +"enormous distance to the sunless sea below.\n");


}
