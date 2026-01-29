#include "defs.h"

inherit CORRIDOR;

void
create_room()
{
    create_corridor();

    add_exit(RUIN + "build7_1", "north");
    add_exit(RUIN + "build6", "south");
}
