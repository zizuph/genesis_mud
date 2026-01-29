#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_forest();
    add_exit(FOREST + "s_forest_4", "north");
    add_exit(FOREST + "s_forest_13", "east");
    add_exit(FOREST + "s_forest_20", "south");
    add_exit(FOREST + "s_forest_11", "west");
}
