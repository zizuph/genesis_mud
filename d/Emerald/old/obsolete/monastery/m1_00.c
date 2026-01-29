#include "/d/Emerald/defs.h"
#include "defs.h"

inherit M1_OUT_BASE;

nomask void
create_m1_room()
{
    add_walkway();

    add_exit("m2_00", "up");
    add_exit("m1_10", "east");
    add_exit("m1_01", "north");
    add_exit("m1_11", "northeast");
    add_exit(KROAD_DIR + "coast9", "west");

    load_clone_handler = 1;
}
