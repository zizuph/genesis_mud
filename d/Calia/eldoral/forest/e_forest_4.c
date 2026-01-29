#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_wall("west");
    create_special(SINKHOLE, "east");
    create_forest();    

    add_exit(FOREST + "e_forest_6", "north");
    add_exit(FOREST + "e_forest_2", "south");
}
