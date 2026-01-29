#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_wall("north");
    create_forest();
    add_exit(FOREST + "w_forest_12", "west");
    add_exit(FOREST + "s_forest_8", "south");
    add_exit(RUIN + "south_entry", "east");
}
