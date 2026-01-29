#include "defs.h"

inherit M1_OUT_BASE;

nomask void
create_m1_room()
{
    add_walkway();

    add_exit("m1_13", "east");
    add_exit("m1_02", "south");
    add_exit("m1_12", "southeast");
}
