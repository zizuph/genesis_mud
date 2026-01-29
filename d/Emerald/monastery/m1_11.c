#include "defs.h"

inherit M1_OUT_BASE;

nomask void
create_m1_room()
{
    add_garden();

    add_exit("m1_21", "east");
    add_exit("m1_01", "west");
    add_exit("m1_12", "north");
    add_exit("m1_10", "south");
    add_exit("m1_22", "northeast");
    add_exit("m1_20", "southeast");
    add_exit("m1_02", "northwest");
    add_exit("m1_00", "southwest");
}
