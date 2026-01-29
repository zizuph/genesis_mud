#include "defs.h"

inherit M0_IN_BASE;

nomask void
create_m0_room()
{
    add_exit("m0_32", "west");
    add_exit("m0_41", "south");
    add_exit("m0_31", "southwest");
}
