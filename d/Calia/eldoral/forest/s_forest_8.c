#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_forest();
    add_exit(FOREST + "s_forest_1", "north");
    add_exit(FOREST + "s_forest_9", "east");
    add_exit(FOREST + "s_forest_18", "south");
    add_exit(FOREST + "w_forest_14", "west");
}
