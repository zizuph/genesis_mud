#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_shore("east and south");
    create_special(SINKHOLE, "west");
    create_forest();    

    add_exit(FOREST + "e_forest_7", "north");
    add_exit(SHORE + "shore10", "east", "@@shore_msg");
    add_exit(SHORE + "shore9", "south", "@@shore_msg"); 
}
