#include "defs.h"

inherit CAVBASE;

public int
go_down()
{
    if (block_exit())
        return 1;
    write("The slope steeps sharply downwards, then through a " +
        "switchback, and you emerge on a lower level heading " +
        "westwards.\n");
    return 0;
}

public void
create_room()
{
    create_cavern(2);
    dir_up = ({"north"});
    dir_down = ({"east"});
    dir_level = ({"southwest"});
    create_base();
    add_exit(CAVERNS + "cav17", "north", "@@block_exit");
    add_exit(CAVERNS + "cav12", "southwest");
    add_exit(CAVERNS + "cav18", "east", "@@go_down");
}
