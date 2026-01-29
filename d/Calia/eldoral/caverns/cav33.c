#include "defs.h"

inherit CAVBASE;

public void
create_room()
{
    create_tunnel(3);
    dir_down = ({"southeast", "southwest"});
    create_base();
    add_exit(CAVERNS + "cav34", "southeast", "@@block_exit");
    add_exit(CAVERNS + "cav32", "southwest");
}
