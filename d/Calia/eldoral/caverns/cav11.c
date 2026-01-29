#include "defs.h"

inherit CAVBASE;

public void
create_room()
{
    create_tunnel(3);
    dir_down = ({"southeast"});
    dir_level = ({"southwest"});
    create_base();
    add_exit(CAVERNS + "cav12", "southeast", "@@block_exit");
    add_exit(CAVERNS + "cav8", "southwest");
}
