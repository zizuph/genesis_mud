#include "defs.h"

inherit CAVBASE;

public void
create_room()
{
    create_tunnel(2);
    dir_down = ({"south"});
    dir_level = ({"southwest"});
    create_base();
    add_exit(CAVERNS + "cav8", "south", "@@block_exit");
    add_exit(CAVERNS + "cav5", "southwest");
}
