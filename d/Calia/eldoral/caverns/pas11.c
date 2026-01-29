#include "defs.h"

inherit CAVBASE;

public void
create_room()
{
    create_tunnel(2);
    add_extras(POOLS);
    dir_up = ({"southwest"});
    dir_down = ({"north"});
    create_base();
    add_exit(CAVERNS + "pas10", "north");
    add_exit(CAVERNS + "pas12", "southwest");
}
