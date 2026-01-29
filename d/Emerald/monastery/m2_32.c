#include "defs.h"

inherit M2_IN_BASE;

nomask void
create_m2_room()
{
    add_exit("m2_42", "east");
    add_door_exit(0, MONASTERY_DIR + "m2_22", "west");
    add_exit("m2_33", "north");
    add_exit("m2_31", "south");
    add_exit("m2_43", "northeast");
    add_exit("m2_41", "southeast");
}
