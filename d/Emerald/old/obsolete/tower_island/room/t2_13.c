#include "../defs.h"

inherit T2_IN_BASE;

nomask void
create_t2_room()
{
    add_hallway();

    add_exit("t2_10","northeast");
    add_exit("t2_16","southwest");
    add_exit("t2_17","southeast");

}
