#include "defs.h"

inherit CORRIDOR;

void
create_room()
{
    create_corridor();
    add_exit(RUIN + "build3", "west");
    add_exit(RUIN + "build2", "south");
}
