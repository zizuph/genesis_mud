#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_shore("south");
    create_forest();
    add_exit(FOREST + "w_forest_12", "north");
    add_exit(FOREST + "s_forest_8", "east");
    add_exit(SHORE + "shore27", "south", "@@shore_msg");
    add_exit(FOREST + "w_forest_13", "west");
}
