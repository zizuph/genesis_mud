#include "defs.h"

inherit M1_OUT_BASE;

nomask void
create_m1_room()
{
    add_walkway();

    add_exit("m1_11", "east");
    add_exit("m1_02", "north");
    add_exit("m1_00", "south");
    add_exit("m1_12", "northeast");
    add_exit("m1_10", "southeast");
}
