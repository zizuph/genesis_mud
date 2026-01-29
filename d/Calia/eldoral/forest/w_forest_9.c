#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_forest();
    add_exit(FOREST + "w_forest_6", "north");
    add_exit(FOREST + "w_forest_10", "east");
    add_exit(FOREST + "w_forest_11", "south");
    add_exit(FOREST + "w_forest_8", "west");
}
