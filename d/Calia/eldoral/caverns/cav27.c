#include "defs.h"

inherit CAVBASE;

public void
create_room()
{
    create_cavern(4);
    add_extras(POOLS);
    dir_up = ({"north"});
    dir_down = ({"east"});
    dir_level = ({"southwest"});
    create_base();
    add_exit(CAVERNS + "cav29", "north", "@@block_exit");
    add_exit(CAVERNS + "cav28", "east", "@@block_exit");
    add_exit(CAVERNS + "cav26", "southwest");
}
