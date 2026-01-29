#include "defs.h"

inherit CAVBASE;

public void
create_room()
{
    create_cavern(1);
        dir_up = ({"north", "west"});
    dir_level = ({"northeast"});
    create_base();
    add_exit(CAVERNS + "cav7", "north");
    add_exit(CAVERNS + "cav11", "northeast", "@@block_exit");
    add_exit(CAVERNS + "cav5", "west");
}
