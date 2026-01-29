#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_shore("north and east");
    create_forest();    

    add_exit(SHORE + "shore23", "north", "@@shore_msg");
    add_exit(SHORE + "shore22", "east", "@@shore_msg");
    add_exit(FOREST + "e_forest_30", "south");
    add_exit(FOREST + "e_forest_31", "west");
}
