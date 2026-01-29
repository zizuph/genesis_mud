#include "defs.h"

inherit CAVBASE;

public void
create_room()
{
    create_cavern(4);
    dir_up = ({"northwest"});
    dir_level = ({"east"});
    dir_down = ({"south"});
    create_base();
    add_exit(CAVERNS + "cav37", "northwest", "@@block_exit");
    add_exit(CAVERNS + "cav35", "east");
    add_exit(CAVERNS + "cav34", "south");
}
