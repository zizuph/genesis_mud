#include "defs.h"

inherit M2_OUT_BASE;

int
block()
{
    if (this_player()->query_wiz_level())
    {
        return 0;
    }

    write("A magical force prevents you from going up.\n");
    return 1;
}

nomask void
create_m2_room()
{
    add_exit("m3_03", "up", block);
    add_exit("m2_13", "east");
    add_exit("m2_02", "south");
}
