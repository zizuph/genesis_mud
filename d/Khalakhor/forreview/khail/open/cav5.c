#include "defs.h"

inherit CAVBASE;

public void
create_zombies()
{
    (SPECIAL + "zombie_maker")->wake_up_zombies(TO);
}

public void
create_room()
{
    create_cavern(2);
    dir_up = ({"northwest"});
    dir_level = ({"northeast", "southwest"});
    dir_down = ({"east","southeast","south"});
    create_base();
    add_exit(CAVERNS + "cav7", "northeast", "@@block_exit");
    add_exit(CAVERNS + "cav8", "east", "@@block_exit");
    add_exit(CAVERNS + "cav9", "southeast", "@@block_exit");
    add_exit(CAVERNS + "cav10", "south", "@@block_exit");
    add_exit(CAVERNS + "cav3", "southwest");
    add_exit(CAVERNS + "cav6", "northwest", "@@block_exit");

    set_alarm(0.0, 0.0, create_zombies);
    add_prop(ROOM_I_NO_CLEANUP, 1);
}
