#include "defs.h"

inherit CAVBASE;

public void
create_room()
{
    create_cavern(3);
    add_extras(POOLS);
    dir_up = ({"west", "northwest"});
    dir_level = ({"northeast"});
    dir_down = ({"southeast", "south"});
    create_base();
    add_exit(CAVERNS + "cav16", "northeast", "@@block_exit");
    add_exit(CAVERNS + "cav15", "southeast", "@@block_exit");
    add_exit(CAVERNS + "cav14", "south", "@@block_exit");
    add_exit(CAVERNS + "cav13", "west", "@@block_exit");
    add_exit(CAVERNS + "cav11", "northwest");
}
