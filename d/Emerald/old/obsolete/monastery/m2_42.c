#include "defs.h"

inherit M2_IN_BASE;

nomask void
create_m2_room()
{
    add_exit("m2_52", "east");
    add_exit("m2_32", "west");
    add_exit("m2_43", "north");
    add_exit("m2_41", "south");
    add_exit("m2_53", "northeast");
    add_exit("m2_51", "southeast");
    add_exit("m2_33", "northwest");
    add_exit("m2_31", "southwest");
}
