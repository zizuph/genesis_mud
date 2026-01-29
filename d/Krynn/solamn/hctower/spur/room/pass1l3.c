// pass1l3.c
// grace mar 1995

inherit "/d/Krynn/solamn/hctower/spur/room/std_pass3.c";
#include "../local.h"

void
create_spur_room()
{
   AE(ROOM + "inn", "east", 0);
   AE(ROOM + "kn1", "west", 0);
   AE(ROOM + "pass2l3", "north", 0);
   AE(ROOM + "landing4", "south", 0);

   make_room("\n   This passage continues north and south " +
        "toward two different stairwells.  There is an archway to "+
        "the east that opens onto the Refectory. West is a comfort"+
        "able sitting room where Knights tend to congregate.\n");
}


