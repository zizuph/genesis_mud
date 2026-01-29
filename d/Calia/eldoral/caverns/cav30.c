#include "defs.h"

inherit CAVBASE;

public int
go_down()
{
    write("As you head through the passage, you notice it dip " +
        "sharply, taking you down onto a different level.\n");
    return 0;
}

public void
create_room()
{
    create_tunnel(2);
    dir_up = ({"north"});
    dir_down = ({"south"});
    create_base();
    add_exit(CAVERNS + "cav31", "north", "@@block_exit");
    add_exit(CAVERNS + "cav29", "south", "@@go_down");
}
