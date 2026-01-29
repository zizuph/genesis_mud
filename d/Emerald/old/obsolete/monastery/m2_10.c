#include "defs.h"

inherit M2_OUT_BASE;

nomask void
create_m2_room()
{
    add_exit("m2_20", "east");
    add_exit("m2_00", "west");
}
