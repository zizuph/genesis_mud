#include "defs.h"

inherit CORRIDOR;

void
create_room()
{
    create_corridor();

    add_exit(RUIN + "build2", "north");
    add_exit(RUIN + "build1", "south");
}
