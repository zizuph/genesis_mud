#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_shore("east and south");
    create_special(SINKHOLE, "west");
    create_forest();    

    add_exit(SHORE + "shore12", "north", "@@shore_msg"); 
    add_exit(SHORE + "shore11", "east", "@@shore_msg");
    add_exit(FOREST + "e_forest_5", "south");
}
