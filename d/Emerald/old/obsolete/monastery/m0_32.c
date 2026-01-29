#include "defs.h"

inherit M0_IN_BASE;

nomask void
create_m0_room()
{
    add_exit("m0_42", "east");
    add_exit("m0_22", "west");
    add_exit("m0_31", "south");
    add_exit("m0_41", "southeast");
}
