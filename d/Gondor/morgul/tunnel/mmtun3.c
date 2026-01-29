inherit "/d/Gondor/morgul/tunnel/std_tunnel";
#include "/d/Gondor/defs.h"

void
create_room()
{
    add_exit(MORGUL_DIR + "tunnel/mmtun2", "north", 0, 5);
    add_exit(MORGUL_DIR + "tunnel/detun4se", "southeast", 0, 3);
    add_exit(MORGUL_DIR + "tunnel/mmtun4", "southwest", 0, 3);

    make_the_room("The tunnel continues to descend steeply towards " +
        "the southwest and southeast, while leading upwards to the north. ");

    (MORGUL_DIR + "tunnel/detun4se")->load_me();
}
