#pragma strict_types

#include "defs.h"

inherit NEWALKBASE;

public void
create_room()
{
    create_walk("south");

    add_exit(RUIN + "ne_walk_3", "west");
    add_exit(RUIN + "ne_walk_5", "east");
}
