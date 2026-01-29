#include "defs.h"

inherit CAVBASE;

public void
create_room()
{
    create_tunnel(1);
    add_extras(POOLS);
    dir_up = ({"northeast"});
    dir_down = ({"south"});
    create_base();
    add_exit(CAVERNS + "pas2", "northeast");
    add_exit(CAVERNS + "pas4", "south");
}
