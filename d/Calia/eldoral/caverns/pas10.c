#include "defs.h"

inherit CAVBASE;

public void
create_room()
{
    create_tunnel(3);
    add_extras(POOLS);
    dir_down = ({"northeast"});
    dir_up = ({"south"});
    create_base();
    add_exit(CAVERNS + "pas9", "northeast");
    add_exit(CAVERNS + "pas11", "south");
}
