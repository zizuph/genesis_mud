#include "defs.h"

inherit CAVBASE;

public void
create_room()
{
    create_cavern(1);
    add_extras(POOLS);
    dir_up = ({"north", "northwest"});
    create_base();
    add_exit(CAVERNS + "cav3", "north", "@@block_exit");
    add_exit(CAVERNS + "cav2", "northwest");
}
