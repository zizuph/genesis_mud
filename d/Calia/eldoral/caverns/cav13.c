#include "defs.h"

inherit CAVBASE;

public void
create_room()
{
    create_tunnel(2);
    dir_down = ({"east"});
    create_base();
    add_exit(CAVERNS + "cav12", "east");
}
