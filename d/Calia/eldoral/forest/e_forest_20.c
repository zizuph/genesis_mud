#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_shore("east");
    create_special(SHRINE, "north");
    create_forest();    

    add_exit(SHORE + "shore17", "east", "@@shore_msg");
    add_exit(FOREST + "e_forest_17", "south");
    add_exit(FOREST + "e_forest_19", "west");
}
