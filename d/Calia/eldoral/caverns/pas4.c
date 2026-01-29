#include "defs.h"

inherit CAVBASE;

public void
create_room()
{
    create_tunnel(2);
    dir_up = ({"north"});
    dir_down = ({"southeast"});
    create_base();
    add_exit(CAVERNS + "pas3", "north");
    add_exit(CAVERNS + "pas5", "southeast");
}
