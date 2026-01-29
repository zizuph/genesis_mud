#include "defs.h"

inherit CAVBASE;

public void
create_room()
{
    create_tunnel(1);
    dir_up = ({"northwest"});
    dir_down = ({"southwest"});
    create_base();
    add_exit(CAVERNS + "pas1", "northwest");
    add_exit(CAVERNS + "pas3", "southwest");
}
