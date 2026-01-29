#include "defs.h"

inherit M1_OUT_BASE;

nomask void
create_m1_room()
{
    add_garden();

    add_exit("m1_22", "east");
    add_exit("m1_02", "west");
    add_exit("m1_13", "north");
    add_exit("m1_11", "south");
    add_exit("m1_23", "northeast");
    add_exit("m1_21", "southeast");
    add_exit("m1_03", "northwest");
    add_exit("m1_01", "southwest");
}
