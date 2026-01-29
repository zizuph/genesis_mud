#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_forest();
    add_exit(RUIN + "south_entry", "north");
    add_exit(FOREST + "s_forest_10", "east");
    add_exit(FOREST + "s_forest_19", "south");
    add_exit(FOREST + "s_forest_8", "west");
}
