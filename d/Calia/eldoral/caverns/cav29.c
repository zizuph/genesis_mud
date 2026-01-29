#include "defs.h"

inherit CAVBASE;

public int
go_up()
{
    if (block_exit())
        return 1;
    write("You head northwards, and find the passage suddenly climbs " +
        "sharply, upwards onto a different level.\n");
    return 0;
}

public void
create_room()
{
    create_cavern(3);
    dir_up = ({"north"});
    dir_down = ({"south"});
    create_base();
    add_exit(CAVERNS + "cav30", "north", "@@go_up");
    add_exit(CAVERNS + "cav27", "south");
}
