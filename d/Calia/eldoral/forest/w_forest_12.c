#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_forest();
    add_exit(FOREST + "w_forest_10", "north");
    add_exit(FOREST + "s_forest_1", "east");
    add_exit(FOREST + "w_forest_14", "south");
    add_exit(FOREST + "w_forest_11", "west");
}
