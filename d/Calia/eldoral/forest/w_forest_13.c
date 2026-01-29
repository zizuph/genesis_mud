#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_shore("south and west");
    create_forest();
    add_exit(FOREST + "w_forest_11", "north");
    add_exit(FOREST + "w_forest_14", "east");
    add_exit(SHORE + "shore26", "south", "@@shore_msg");
    add_exit(SHORE + "shore25", "west", "@@shore_msg");
}
