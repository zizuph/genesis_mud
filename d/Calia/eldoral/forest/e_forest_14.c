#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_shore("east and south");
    create_special(BOULDERS, "north");
    create_forest();    

    add_exit(SHORE + "shore14", "east", "@@shore_msg");
    add_exit(SHORE + "shore13", "south", "@@shore_msg");
    add_exit(FOREST + "e_forest_13", "west");
}
