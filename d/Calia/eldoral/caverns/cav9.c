#include "defs.h"

inherit CAVBASE;

public void
create_room()
{
    create_tunnel(2);
    add_extras(POOLS);
    dir_up = ({"northwest"});
    create_base();
    add_exit(CAVERNS + "cav5", "northwest");
}
