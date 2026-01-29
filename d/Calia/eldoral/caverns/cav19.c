#include "defs.h"

inherit CAVBASE;

public void
create_room()
{
    create_tunnel(2);
    dir_up = ({"north"});
    dir_level = ({"northeast"});
    create_base();
    add_exit(CAVERNS + "cav18", "northeast");
    add_exit(CAVERNS + "cav20", "north", "@@block_exit");
}
