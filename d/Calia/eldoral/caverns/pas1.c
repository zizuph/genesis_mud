#include "defs.h"

inherit CAVBASE;

public int
out_msg()
{
    write("You emerge from the entrance to the passage and take " +
        "a deep breath of fresh air.\n");
    return 0;
}

public void
create_room()
{
    create_tunnel(1);
    dir_up = ({"north"});
    dir_down = ({"southeast"});
    create_base();
    add_exit(FOREST + "s_forest_17", "north", "@@out_msg");
    add_exit(CAVERNS + "pas2", "southeast");
}
