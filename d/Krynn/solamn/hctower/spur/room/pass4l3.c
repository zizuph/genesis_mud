// pass4l3.c
// grace mar 1995

inherit "/d/Krynn/solamn/hctower/spur/room/std_pass3.c";
#include "../local.h"

void
create_spur_room()
{
   AE(ROOM + "stair11", "north", 0);
   AE(ROOM + "pass3l3", "south", 0);

   make_room("\n   The stairwell leading up to the battlements "+
        "lies north.  In the far southern end of the passage is another "+
        "stairway.  The scent of food and the sound of voices comes "+
        "from south of here.\n");
}


