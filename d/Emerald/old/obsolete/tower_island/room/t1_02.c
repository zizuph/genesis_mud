#include "../defs.h"

inherit T1_IN_BASE;

nomask void
create_t1_room()
{
    add_hallway();

    add_exit("t1_05", "southwest");
    add_exit("t1_09", "south");
    add_exit("t1_06", "southeast");
}
