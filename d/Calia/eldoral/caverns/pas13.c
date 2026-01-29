#include "defs.h"

inherit CAVBASE;

public void
create_room()
{
    create_tunnel(1);
    dir_up = ({"south"});
    dir_down = ({"north"});
    create_base();
    add_exit(CAVERNS + "pas12", "north");
    add_exit(MOUNT + "secret", "south");
}
