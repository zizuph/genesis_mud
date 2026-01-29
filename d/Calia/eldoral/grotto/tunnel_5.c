#include "../caverns/defs.h"

inherit CAVBASE;

public void
create_room()
{
    create_tunnel(2);
    dir_down = ({"south"});
    dir_level = ({"northwest"});
    create_base();

    add_exit(GROTTO + "tunnel_6", "south");
    add_exit(GROTTO + "tunnel_4", "northwest");
}
