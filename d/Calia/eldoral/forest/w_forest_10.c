#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_wall("east");
    create_forest();
    add_exit(FOREST + "w_forest_7", "north");
    add_exit(FOREST + "w_forest_12", "south");
    add_exit(FOREST + "w_forest_9", "west");
}
