#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_shore("east");
    create_forest();    

    add_exit(FOREST + "e_forest_32", "north");
    add_exit(SHORE + "shore21", "east", "@@shore_msg");
    add_exit(FOREST + "e_forest_27", "south");
    add_exit(FOREST + "e_forest_29", "west");
}
