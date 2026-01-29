inherit "/d/Gondor/morgul/tunnel/std_tunnel";
#include "/d/Gondor/defs.h"

void
create_room()
{
    add_exit(LAIR_DIR + "tunnel3", "north", 0, 4);
    add_exit(MORGUL_DIR + "tunnel/mmtun2", "down", 0, 4);

    make_the_room("To the north, the small tunnel you are in " +
        "runs into a larger one running from east to west. In " +
        "the other direction, the tunnel makes a bend, at the " +
        "same time going down and turning southwest. ");
}
