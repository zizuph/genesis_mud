#include "defs.h"

inherit CAVBASE;

public void
create_room()
{
    create_tunnel(2);
    dir_level = ({"north"});
    dir_up = ({"southwest"});
    create_base();
    add_exit(CAVERNS + "pas8", "north");
    add_exit(CAVERNS + "pas10", "southwest");
}
