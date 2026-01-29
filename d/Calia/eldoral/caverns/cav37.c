#include "defs.h"

inherit CAVBASE;

public void
create_room()
{
    create_cavern(2);
    dir_up = ({"north"});
    dir_down = ({"southeast"});
    create_base();
    add_exit(RAVINE + "rav1", "north", "@@block_exit");
    add_exit(CAVERNS + "cav36", "southeast");
}
