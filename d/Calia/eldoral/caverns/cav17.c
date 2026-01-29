#include "defs.h"

inherit CAVBASE;

public void
create_room()
{
    create_tunnel(1);
    dir_down = ({"south"});
    create_base();
    add_exit(CAVERNS + "cav16", "south");
}
