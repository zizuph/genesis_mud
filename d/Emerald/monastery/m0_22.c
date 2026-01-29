#include "defs.h"

inherit M0_IN_BASE;

nomask void
create_m0_room()
{
    add_exit("m1_22", "up");
    add_exit("m0_32", "east");
}
