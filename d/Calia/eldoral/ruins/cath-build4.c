#include "defs.h"

inherit CORRIDOR;

public int
south_msg()
{
    write("You emerge from the hallway, and descend a flight of steps " +
        "into a large room.\n");
    return 0;
}

public void
create_room()
{
    create_corridor();
    add_exit(RUIN + "build4_e", "north");
    add_exit(RUIN + "s_cathedral", "south", "@@south_msg");
}
