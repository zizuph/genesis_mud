#include "../defs.h"

inherit T2_IN_BASE;

nomask void
create_t2_room()
{
    add_hallway();

    add_exit("t2_06","northwest");
    add_exit("t2_07","northeast");
    add_exit("t2_13","southwest");
    add_exit("t2_14","southeast");

}
