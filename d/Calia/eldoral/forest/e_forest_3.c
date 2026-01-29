#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_shore("east and south");
    create_special(SINKHOLE, "north");
    create_forest();    

    add_exit(SHORE + "shore9", "east");
    add_exit(SHORE + "shore8", "south");
    add_exit(FOREST + "e_forest_2", "west");
}
