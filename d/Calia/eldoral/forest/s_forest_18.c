#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_shore("south and west");
    create_forest();
    add_exit(FOREST + "s_forest_8", "north");
    add_exit(FOREST + "s_forest_19", "east");
    add_exit(SHORE + "shore28", "south", "@@shore_msg");
    add_exit(SHORE + "shore27", "west", "@@shore_msg");
}
