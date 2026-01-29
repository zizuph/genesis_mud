#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_shore("east"); 
    create_forest();    

    add_exit(FOREST + "e_forest_13", "north");
    add_exit(SHORE + "shore13", "east", "@@shore_msg");
    add_exit(FOREST + "e_forest_9", "south");
    add_exit(FOREST + "e_forest_10", "west");
}
