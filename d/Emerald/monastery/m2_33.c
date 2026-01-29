#include "defs.h"

inherit M2_IN_BASE;

nomask void
create_m2_room()
{
    add_exit("m2_43", "east");
    add_exit("m2_23", "west");
    add_exit("m2_32", "south");
    add_exit("m2_42", "southeast");
}
