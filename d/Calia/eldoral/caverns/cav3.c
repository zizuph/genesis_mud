#include "defs.h"

inherit CAVBASE;

public void
create_room()
{
    create_tunnel(2);
    add_extras(POOLS);
    dir_up = ({"west"});
    dir_level = ({"northeast"});
    dir_down = ({"south"});
    create_base();
    add_exit(CAVERNS + "cav5", "northeast", "@@block_exit");
    add_exit(CAVERNS + "cav4", "south");
    add_exit(CAVERNS + "cav2", "west");
}
