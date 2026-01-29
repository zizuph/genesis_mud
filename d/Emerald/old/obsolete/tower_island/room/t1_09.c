#include "../defs.h"

inherit T1_IN_BASE;

nomask void
create_t1_room()
{
    add_stairway();

    add_exit("t1_02", "north");
    add_exit("t2_09", "up");
}
