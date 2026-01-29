#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_cliff();
    create_forest();
    create_shore("south");
    add_exit(FOREST + "w_forest_5", "north");
    add_exit(FOREST + "w_forest_9", "east");
    add_exit(SHORE + "shore24", "south", "@@shore_msg");
}
