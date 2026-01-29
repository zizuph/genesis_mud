#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_shore("west and south");
    create_forest();

    add_exit(FOREST + "s_forest_27", "north");
    add_exit(FOREST + "s_forest_35", "east");
    add_exit(SHORE + "shore30", "south", "@@shore_msg");
    add_exit(SHORE + "shore29", "west");
}
