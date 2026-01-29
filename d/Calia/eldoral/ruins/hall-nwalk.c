#include "defs.h"

inherit CORRIDOR;

void
create_room()
{
    create_corridor();
    add_exit(RUIN + "nwalk1", "north");
    add_exit(RUIN + "main_hall_2", "south");
}
