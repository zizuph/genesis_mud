#include "defs.h"

inherit CAVBASE;

public void
create_room()
{
    create_tunnel(1);
    dir_up = ({"northwest"});
    dir_down = ({"southeast"});
    create_base();
    add_exit(CAVERNS + "pas4", "northwest");
    add_exit(CAVERNS + "pas6", "southeast");
}
