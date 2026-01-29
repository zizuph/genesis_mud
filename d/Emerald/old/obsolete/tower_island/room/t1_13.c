#include "../defs.h"

inherit T1_IN_BASE;

nomask void
create_t1_room()
{
    add_hallway();

    add_exit("t1_10", "northeast");
    add_exit("t1_16", "southwest");
    add_exit("t1_17", "southeast");
}
