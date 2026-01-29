#include "defs.h"

inherit CAVBASE;

public void
create_room()
{
    create_cavern(2);
    dir_down = ({"southwest"});
    dir_level = ({"west"});
    create_base();
    add_exit(CAVERNS + "cav34", "southwest");
    add_exit(CAVERNS + "cav36", "west", "@@block_exit");
}
