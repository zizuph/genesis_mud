#include "defs.h"

inherit CAVBASE;

public void
create_room()
{
    create_tunnel(3);
    dir_up = ({"west"});
    dir_level = ({"northeast"});
    create_base();
    add_exit(CAVERNS + "entrance", "west");
    add_exit(CAVERNS + "cav2", "northeast", "@@block_exit");
}
