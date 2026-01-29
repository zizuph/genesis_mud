#include "defs.h"

inherit CAVBASE;

public void
create_room()
{
    create_tunnel(3);
    dir_level = ({"southwest"});
    dir_down = ({"east", "southeast"});
    create_base();
    add_exit(CAVERNS + "cav3", "east", "@@block_exit");
    add_exit(CAVERNS + "cav4", "southeast", "@@block_exit");
    add_exit(CAVERNS + "cav1", "southwest");
}
