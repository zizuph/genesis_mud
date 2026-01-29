#include "../defs.h"

inherit T1_OUT_BASE;

nomask void
create_t1_room()
{
    add_walkway();

    add_exit("t1_19", "north");
    add_exit("t1_24", "south");
    add_exit("t1_23", "southwest");
    add_exit("t1_25", "southeast");
}
