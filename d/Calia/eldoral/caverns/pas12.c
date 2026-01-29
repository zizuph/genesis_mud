#include "defs.h"

inherit CAVBASE;

public void
create_room()
{
    create_tunnel(2);
    dir_up = ({"south"});
    dir_down = ({"northeast"});
    create_base();
    add_exit(CAVERNS + "pas11", "northeast");
    add_exit(CAVERNS + "pas13", "south");
}
