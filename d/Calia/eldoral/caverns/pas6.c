#include "defs.h"

inherit CAVBASE;

public void
create_room()
{
    create_tunnel(3);
    add_extras(POOLS);
    dir_up = ({"northwest"});
    dir_down = ({"southwest"});
    create_base();
    add_exit(CAVERNS + "pas5", "northwest");
    add_exit(CAVERNS + "pas7", "southwest");
}
