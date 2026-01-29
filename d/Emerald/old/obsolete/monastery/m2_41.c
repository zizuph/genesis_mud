#include "defs.h"

inherit M2_IN_BASE;

nomask void
create_m2_room()
{
    add_exit("m2_51", "east");
    add_exit("m2_31", "west");
    add_exit("m2_42", "north");
    add_exit("m2_40", "south");
    add_exit("m2_52", "northeast");
    add_exit("m2_50", "southeast");
    add_exit("m2_32", "northwest");
    add_exit("m2_30", "southwest");
}
