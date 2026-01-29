#include "defs.h"

inherit CAVBASE;

public void
create_room()
{
    create_tunnel(3);
    dir_down = ({"southeast"});
    dir_level = ({"northeast"});
    create_base();
    add_exit(CAVERNS + "cav27", "northeast", "@@block_exit");
    add_exit(CAVERNS + "cav25", "southeast");
}
