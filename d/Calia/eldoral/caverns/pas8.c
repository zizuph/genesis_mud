#include "defs.h"

inherit CAVBASE;

public void
create_room()
{
    create_tunnel(3);
    dir_level = ({"north", "south"});
    create_base();
    add_exit(CAVERNS + "pas7", "north");
    add_exit(CAVERNS + "pas9", "south");
}
