#include "defs.h"

inherit CAVBASE;

public void
create_room()
{
    create_cavern(2);
    dir_up = ({"north"});
    dir_down = ({"south"});
    dir_level = ({"southwest"});
    create_base();
    add_exit(CAVERNS + "cav21", "north");
    add_exit(CAVERNS + "cav23", "south", "@@block_exit");
    add_exit(CAVERNS + "cav24", "southwest", "@@block_exit");
}
