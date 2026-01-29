#include "defs.h"

inherit M2_IN_BASE;

nomask void
create_m2_room()
{
    add_exit("m2_30", "west");
    add_exit("m2_50", "east");
    add_exit("m2_41", "north");
    add_exit("m2_31", "northwest");
    add_exit("m2_51", "northeast");
}
