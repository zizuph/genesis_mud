#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_wall("west");
    create_special(SINKHOLE, "east");
    create_forest();    

    add_exit(FOREST + "e_forest_8", "north");
    add_exit(FOREST + "e_forest_4", "south");
}
