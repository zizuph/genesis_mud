#include "defs.h"

inherit M2_IN_BASE;

nomask void
create_m2_room()
{
    add_exit("m2_53", "east");
    add_exit("m2_33", "west");
    add_exit("m2_42", "south");
    add_exit("m2_52", "southeast");
    add_exit("m2_32", "southwest");
}
