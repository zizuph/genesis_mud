#include "defs.h"

inherit M2_IN_BASE;

nomask void
create_m2_room()
{
    add_exit("m2_41", "east");
    add_door_exit(0, MONASTERY_DIR + "m2_21", "west");
    add_exit("m2_32", "north");
    add_exit("m2_30", "south");
    add_exit("m2_42", "northeast");
    add_exit("m2_40", "southeast");
}
