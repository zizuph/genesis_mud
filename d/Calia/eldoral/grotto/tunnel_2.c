#include "../caverns/defs.h"

inherit CAVBASE;

public void
create_room()
{
    create_tunnel(1);
    dir_up = ({"northeast"});
    dir_down = ({"west"});
    create_base();

    add_exit(GROTTO + "tunnel_3", "northeast");
    add_exit(GROTTO + "tunnel_1", "west");
}
