#pragma strict_types

#include "defs.h"

inherit NEWALKBASE;

public void
create_room()
{
    extra = "The walkway turns here, angling away to the north " +
        "and east along the edges of the courtyard. A narrow " +
        "alley of some sort leads to the south between two " +
        "high walls from here.";

    create_walk("southwest");

    add_exit(RUIN + "ne_walk_2", "north");
    add_exit(RUIN + "ne_walk_4", "east");
    add_exit(RUIN + "ne_alley", "south");
}
