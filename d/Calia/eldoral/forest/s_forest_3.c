#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_wall("north");
    create_forest();
    add_exit(FOREST + "s_forest_4", "east");
    add_exit(FOREST + "s_forest_2", "west");
    add_exit(FOREST + "s_forest_11", "south");
}
