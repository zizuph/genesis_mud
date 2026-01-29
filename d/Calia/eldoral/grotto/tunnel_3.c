#include "../caverns/defs.h"

inherit CAVBASE;

public void
create_room()
{
    create_tunnel(2);
    dir_up = ({"east"});
    dir_down = ({"southwest"});
    create_base();

    add_exit(GROTTO + "tunnel_4", "east");
    add_exit(GROTTO + "tunnel_2", "southwest");
}
