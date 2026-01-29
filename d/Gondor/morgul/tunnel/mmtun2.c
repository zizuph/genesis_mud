inherit "/d/Gondor/morgul/tunnel/std_tunnel";
#include "/d/Gondor/defs.h"

void
create_room()
{
    add_exit(MORGUL_DIR + "tunnel/mmtun1", "up", 0, 5);
    add_exit(MORGUL_DIR + "tunnel/mmtun3", "south", 0, 3);
    add_exit(MORGUL_DIR + "tunnel/detun3sw", "southwest", 0, 3);

    make_the_room("The tunnel splits into two directions, one to the " +
        "south, the other to the southwest. Both tunnels slope downwards, " +
        "but the one to the southwest is the steepest. "); 

    (MORGUL_DIR + "tunnel/detun3sw")->load_me();
}
