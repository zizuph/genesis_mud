#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_wall("west");
    create_special(SHRINE, "east");
    create_forest();    

    add_exit(FOREST + "e_forest_23", "north");
    add_exit(FOREST + "e_forest_19", "south");
}
