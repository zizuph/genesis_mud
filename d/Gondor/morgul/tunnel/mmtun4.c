inherit "/d/Gondor/morgul/tunnel/std_tunnel";
#include "/d/Gondor/defs.h"

void
create_room()
{
    add_exit(MORGUL_DIR + "tunnel/mmtun3", "up", 0, 4);
    add_exit(MORGUL_DIR + "tunnel/mmtun5", "down", 0, 4);

    make_the_room("The tunnel continues to descend steeply towards " +
        "the southwest, leading upwards to the northeast. ");
}
