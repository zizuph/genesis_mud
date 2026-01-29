#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_special(SHRINE, "west");
    create_forest();
    add_exit(FOREST + "s_forest_16", "north");
    add_exit(FOREST + "s_forest_25", "east");
    add_exit(FOREST + "s_forest_33", "south");
}
