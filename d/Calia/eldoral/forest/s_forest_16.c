#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_forest();
    add_exit(FOREST + "s_forest_6", "north");
    add_exit(FOREST + "s_forest_17", "east");
    add_exit(FOREST + "s_forest_24", "south");
    add_exit(FOREST + "s_forest_15", "west");
}
