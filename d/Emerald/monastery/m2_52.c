#include "defs.h"

inherit M2_IN_BASE;

nomask void
create_m2_room()
{
    add_exit("m2_42", "west");
    add_exit("m2_53", "north");
    add_exit("m2_51", "south");
    add_exit("m2_43", "northwest");
    add_exit("m2_41", "southwest");
}
