#include "defs.h"

inherit CORRIDOR;

void
create_room()
{
    create_corridor();
    add_exit(RUIN + "main_hall_1", "north");
    add_exit(RUIN + "build4_w", "south");
}
