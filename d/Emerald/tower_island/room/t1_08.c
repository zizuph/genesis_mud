#include "../defs.h"

inherit T1_IN_BASE;

nomask void
create_t1_room()
{
    add_hallway();

    add_exit("t1_04", "northwest");
    add_exit("t1_05", "northeast");
    add_exit("t1_11", "southwest");
    add_exit("t1_12", "southeast");
}
