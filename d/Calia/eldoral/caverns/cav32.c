#include "defs.h"

inherit CAVBASE;

public void
create_room()
{
    create_tunnel(3);
    add_extras(POOLS);
    dir_up = ({"northeast"});
    dir_level = ({"east"});
    create_base();
    add_exit(CAVERNS + "cav33", "northeast", "@@block_exit");
    add_exit(CAVERNS + "cav31", "east");
}
