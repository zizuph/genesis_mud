#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_wall("north");
    create_forest();
    add_exit(FOREST + "s_forest_7", "east");
    add_exit(FOREST + "s_forest_16", "south");
    add_exit(FOREST + "s_forest_5", "west");
}
