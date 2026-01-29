#include "defs.h"

inherit CAVBASE;

public void
create_room()
{
    create_cavern(2);
    dir_up = ({"north"});
    dir_level = ({"northeast"});
    create_base();
    add_exit(CAVERNS + "cav22", "northeast");
    add_exit(CAVERNS + "cav25", "north", "@@block_exit");
}
