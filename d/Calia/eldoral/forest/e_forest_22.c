#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_shore("east and south");
    create_special(SHRINE, "west");
    create_forest();    

    add_exit(FOREST + "e_forest_25", "north");
    add_exit(SHORE + "shore18", "east", "@@shore_msg");
    add_exit(SHORE + "shore17", "south", "@@shore_msg");
}
