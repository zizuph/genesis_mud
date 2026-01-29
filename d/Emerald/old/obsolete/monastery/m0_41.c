#include "defs.h"

inherit M0_IN_BASE;

nomask void
create_m0_room()
{
    add_exit("m0_42", "north");
    add_exit("m0_31", "west");
    add_exit("m0_32", "northwest");
}
