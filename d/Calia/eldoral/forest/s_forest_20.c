#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_special(BUILD_RUINS, "west");
    create_forest();
    add_exit(FOREST + "s_forest_12", "north");
    add_exit(FOREST + "s_forest_21", "east");
    add_exit(FOREST + "s_forest_29", "south");
}
