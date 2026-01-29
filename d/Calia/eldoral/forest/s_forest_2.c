#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_wall("north");
    create_forest();
    add_exit(RUIN + "south_entry", "west");
    add_exit(FOREST + "s_forest_10", "south");
    add_exit(FOREST + "s_forest_3", "east");
}
