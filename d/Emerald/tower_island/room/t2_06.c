#include "../defs.h"

inherit T2_IN_BASE;

nomask void
create_t2_room()
{
    add_hallway();

    add_exit("t2_02","northwest");
    add_exit("t2_03","northeast");
    add_exit("t2_10","southeast");

}
