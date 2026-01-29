#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_special(BUILD_RUINS, "south");
    create_forest();
    add_exit(FOREST + "s_forest_2", "north");
    add_exit(FOREST + "s_forest_11", "east");
    add_exit(FOREST + "s_forest_9", "west");
}
