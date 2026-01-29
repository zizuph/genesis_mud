#include "defs.h"

inherit CAVBASE;

public void
create_room()
{
    create_tunnel(1);
    dir_down = ({"southeast"});
    create_base();
    add_exit(CAVERNS + "cav5", "southeast");
}
