#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_forest();

    add_exit(FOREST + "s_forest_21", "north");
    add_exit(FOREST + "s_forest_31", "east");
    add_exit(FOREST + "s_forest_37", "south");
    add_exit(FOREST + "s_forest_29", "west");
}
