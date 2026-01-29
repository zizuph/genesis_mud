#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_shore("west");
    create_forest();
    add_exit(FOREST + "w_forest_9", "north");
    add_exit(FOREST + "w_forest_12", "east");
    add_exit(FOREST + "w_forest_13", "south");
    add_exit(SHORE + "shore24", "west", "@@shore_msg");
}
