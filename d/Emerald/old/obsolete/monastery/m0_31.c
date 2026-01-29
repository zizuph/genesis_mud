#include "defs.h"

inherit M0_IN_BASE;

nomask void
create_m0_room()
{
    add_exit("m0_32", "north");
    add_exit("m0_41", "east");
    add_exit("m0_21", "west");
    add_exit("m0_42", "northeast");
}
