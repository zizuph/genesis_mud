#include "../defs.h"

inherit T2_IN_BASE;

nomask void
create_t2_room()
{
    add_hallway();

    add_exit("t2_12","northwest");
    add_exit("t2_13","northeast");

}
