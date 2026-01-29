#include "../defs.h"

inherit T1_IN_BASE;

nomask void
create_t1_room()
{
    add_entrance();

    add_exit("t1_16", "north");
    add_exit("t1_22", "south");
    add_exit("t1_18", "west");
    add_exit("t1_20", "east");
}
