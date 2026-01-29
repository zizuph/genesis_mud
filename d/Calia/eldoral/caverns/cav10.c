#include "defs.h"

inherit CAVBASE;

public void
create_room()
{
    create_tunnel(1);
    dir_up = ({"north"});
    create_base();
    add_exit(CAVERNS + "cav5", "north");
}
