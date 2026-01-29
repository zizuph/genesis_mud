#include "defs.h"

inherit M1_OUT_BASE;

nomask void
create_m1_room()
{
    add_walkway();

    add_exit("m1_23", "east");
    add_exit("m1_03", "west");
    add_exit("m1_12", "south");
    add_exit("m1_22", "southeast");
    add_exit("m1_02", "southwest");
}
