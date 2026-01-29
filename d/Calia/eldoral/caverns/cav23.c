#include "defs.h"

inherit CAVBASE;

public void
create_room()
{
    create_cavern(1);
    add_extras(POOLS);
    dir_up = ({"north"});
    create_base();
    add_exit(CAVERNS + "cav22", "north");
}
