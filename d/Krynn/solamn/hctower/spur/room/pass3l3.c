// pass3l3.c
// grace mar 1995

inherit "/d/Krynn/solamn/hctower/spur/room/std_pass3.c";
#include "../local.h"

void
create_spur_room()
{
   AE(ROOM + "pass4l3", "north", 0);
   AE(ROOM + "pass2l3", "south", 0);
   AE(ROOM + "kn2", "west", 0);

   make_room("\n   This passage continues north and south " +
        "toward two different stairwells.  There is a wide door"+
        "way leading west.\n");
 
}


