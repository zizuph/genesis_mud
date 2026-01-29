#include "defs.h"

inherit CAVBASE;

public void
create_room()
{
    create_cavern(3);
    add_extras(POOLS);
    dir_down = ({"southeast", "south"});
    dir_level = ({"southwest"});
    create_base();
    add_exit(CAVERNS + "cav20", "southeast");
    add_exit(CAVERNS + "cav22", "south", "@@block_exit");
    add_exit(CAVERNS + "cav25", "southwest", "@@block_exit");
}
