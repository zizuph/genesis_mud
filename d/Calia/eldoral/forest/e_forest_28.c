#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_shore("north and east");
    create_forest();    

    add_exit(SHORE + "shore21", "north", "@@shore_msg");
    add_exit(SHORE + "shore20", "east", "@@shore_msg");
    add_exit(FOREST + "e_forest_25", "south");
    add_exit(FOREST + "e_forest_27", "west");
}
