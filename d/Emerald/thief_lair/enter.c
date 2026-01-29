inherit "/std/room";

#include "/d/Emerald/defs.h"

void
create_room()
{
    set_short("Atop a rock outcrop");

    set_long("A narrow outcrop juts out from the steep face of the " +
        "mountain.  Glancing around, you notice a small, dark  cave " +
        "opening to the north, almost indistinguishable from the " +
        "black stone of the mountain face.\n");

    add_exit("cave", "north");
    add_exit(MBLACK_DIR + "path3", "down", 0, 3);
}

