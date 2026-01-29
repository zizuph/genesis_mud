#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_shore("east"); 
    create_special(SINKHOLE, "south");
    create_forest();    

    add_exit(FOREST + "e_forest_11", "north");
    add_exit(SHORE + "shore12", "east", "@@shore_msg");
    add_exit(FOREST + "e_forest_8", "west");
}
