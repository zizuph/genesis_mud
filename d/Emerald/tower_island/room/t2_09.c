#include "../defs.h"

inherit T2_IN_BASE;

nomask void
create_t2_room()
{
    add_dstair();

    add_exit("t1_09","down");
    add_exit("t2_02","north");

}
