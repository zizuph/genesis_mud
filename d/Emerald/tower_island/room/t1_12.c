#include "../defs.h"

inherit T1_IN_BASE;

nomask void
create_t1_room()
{
    add_hallway();

    add_exit("t1_08", "northwest");
    add_exit("t1_15", "southwest");
    add_exit("t1_16", "southeast");
}
