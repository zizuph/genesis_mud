#include "defs.h"

inherit CAVBASE;

public void
create_room()
{
    create_cavern(3);
    add_extras(POOLS);
    dir_up = ({"northwest", "north", "northeast"});
    create_base();
    add_exit(CAVERNS + "cav33", "northwest");
    add_exit(CAVERNS + "cav36", "north", "@@block_exit");
    add_exit(CAVERNS + "cav35", "northeast", "@@block_exit");
}
