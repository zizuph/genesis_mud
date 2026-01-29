#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_shore("east and south");
    create_forest();
    add_exit(FOREST + "s_forest_17", "north");
    add_exit(SHORE + "shore7", "east", "@@shore_msg");
    add_exit(SHORE + "shore6", "south", "@@shore_msg");
    add_exit(FOREST + "s_forest_24", "west");
}
