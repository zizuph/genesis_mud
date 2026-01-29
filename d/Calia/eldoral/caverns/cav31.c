#include "defs.h"

inherit CAVBASE;

public void
create_room()
{
    create_tunnel(3);
    dir_down = ({"south"});
    dir_level = ({"west"});
    create_base();
    add_exit(CAVERNS + "cav30", "south");
    add_exit(CAVERNS + "cav32", "west", "@@block_exit");
}
