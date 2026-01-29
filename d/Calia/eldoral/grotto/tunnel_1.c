#include "../caverns/defs.h"

inherit CAVBASE;

public void
create_room()
{
    create_tunnel(1);
    dir_up = ({"east"});
    dir_down = ({"west"});
    create_base();

    add_exit(GROTTO + "tunnel_2", "east");
    add_exit(GROTTO + "ledge", "west");
}
