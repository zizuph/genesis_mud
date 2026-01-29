#pragma strict_types

#include "defs.h"

inherit NEWALKBASE;

public void
create_room()
{
    create_walk("west");

    add_exit(RUIN + "ne_walk_1", "north");
    add_exit(RUIN + "ne_walk_3", "south");
}
