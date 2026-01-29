#include "defs.h"

inherit CAVBASE;

public void
create_room()
{
    create_tunnel(2);
    dir_up = ({"northeast"});
    dir_level = ({"south"});
    add_extras(POOLS);
    create_base();
    add_exit(CAVERNS + "pas6", "northeast");
    add_exit(CAVERNS + "pas8", "south");
}
