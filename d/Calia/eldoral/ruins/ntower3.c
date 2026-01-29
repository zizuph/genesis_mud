#include "defs.h"

inherit NTOWERBASE;

public void
create_room()
{
    create_tower();

    add_exit(RUIN + "ntower4", "north");
    add_exit(RUIN + "ntower2", "south");
}
