#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_shore("east and south");
    create_forest();
    
    add_exit(FOREST + "e_forest_2", "north");
    add_exit(SHORE + "shore8", "east");
    add_exit(SHORE + "shore7", "south");
    add_exit(FOREST + "s_forest_17", "west");
}
