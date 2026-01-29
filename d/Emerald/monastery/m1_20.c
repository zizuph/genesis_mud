#include "defs.h"

inherit M1_OUT_BASE;

nomask void
create_m1_room()
{
    add_walkway();

    add_exit("m1_10", "west");
    add_exit("m1_21", "north");
    add_exit("m1_11", "northwest");
}
