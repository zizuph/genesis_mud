#include "defs.h"

inherit CAVBASE;

public void
create_room()
{
    create_tunnel(3);
    dir_up = ({"northwest"});
    dir_down = ({"south"});
    create_base();
    add_exit(CAVERNS + "cav19", "south");
    add_exit(CAVERNS + "cav21", "northwest", "@@block_exit");
}
