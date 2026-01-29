inherit "/d/Gondor/morgul/tunnel/std_tunnel";
#include "/d/Gondor/defs.h"

void
create_room()
{
    add_exit(MORGUL_DIR + "tunnel/mmtun4", "up", 0, 4);
    add_exit(MORGUL_DIR + "tunnel/mmtun6", "down", 0, 4);

    make_the_room("You must be far below the surface here. But the tunnel " +
        "still continues to descend steeply towards the southwest, " +
        "while it is leading upwards to the northeast. ");
}
