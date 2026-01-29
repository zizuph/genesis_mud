#include "defs.h"

inherit M1_OUT_BASE;

nomask void
create_m1_room()
{
    add_walkway();

    add_exit("m1_12", "east");
    add_exit("m1_03", "north");
    add_exit("m1_01", "south");
    add_exit("m1_13", "northeast");
    add_exit("m1_11", "southeast");
}
