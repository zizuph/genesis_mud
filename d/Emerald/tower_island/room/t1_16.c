#include "../defs.h"

inherit T1_IN_BASE;

nomask void
create_t1_room()
{
    add_hallway();

    add_exit("t1_12", "northwest");
    add_exit("t1_13", "northeast");
    add_exit("t1_19", "south");
}
