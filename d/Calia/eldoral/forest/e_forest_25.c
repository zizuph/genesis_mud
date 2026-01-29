#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_shore("east");
    create_forest();    

    add_exit(FOREST + "e_forest_28", "north");
    add_exit(SHORE + "shore19", "east", "@@shore_msg");
    add_exit(FOREST + "e_forest_22", "south");
    add_exit(FOREST + "e_forest_24", "west");
}
