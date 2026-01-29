#include "defs.h"

inherit M2_IN_BASE;

nomask void
create_m2_room()
{
    add_exit("m2_43", "west");
    add_exit("m2_52", "south");
    add_exit("m2_42", "southwest");
}
