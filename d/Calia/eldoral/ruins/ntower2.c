#include "defs.h"

inherit NTOWERBASE;

public void
create_room()
{
    create_tower();

    add_exit(RUIN + "ntower3", "north");
    add_exit(RUIN + "ntower1", "south");
}