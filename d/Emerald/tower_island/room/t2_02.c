#include "../defs.h"

inherit T2_IN_BASE;

nomask void
create_t2_room()
{
    add_hallway();

    add_exit("t2_05","southwest");
    add_exit("t2_09","south");
    add_exit("t2_06","southeast");

}
