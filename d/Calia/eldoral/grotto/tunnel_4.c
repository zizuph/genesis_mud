#include "../caverns/defs.h"

inherit CAVBASE;

public void
create_room()
{
    create_tunnel(2);
    dir_level = ({"southeast"});
    dir_down = ({"west"});
    create_base();

    add_exit(GROTTO + "tunnel_5", "southeast");
    add_exit(GROTTO + "tunnel_3", "west");
}
