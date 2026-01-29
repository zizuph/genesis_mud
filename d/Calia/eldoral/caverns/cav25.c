#include "defs.h"

inherit CAVBASE;

public void
create_room()
{
    create_cavern(3);
    dir_up = ({"northwest"});
    dir_level = ({"northeast"});
    dir_down = ({"south"});
    create_base();
    add_exit(CAVERNS + "cav21", "northeast");
    add_exit(CAVERNS + "cav24", "south");
    add_exit(CAVERNS + "cav26", "northwest", "@@block_exit");
}
