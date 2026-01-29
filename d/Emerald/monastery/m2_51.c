#include "defs.h"

inherit M2_IN_BASE;

nomask void
create_m2_room()
{
    add_exit("m2_41", "west");
    add_exit("m2_52", "north");
    add_exit("m2_50", "south");
    add_exit("m2_42", "northwest");
    add_exit("m2_40", "southwest");
}
