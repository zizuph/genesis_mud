#include "defs.h"

inherit SHOREBASE;

public void
create_room()
{
    create_shore();
    create_direction("south");

    add_exit(FOREST + "e_forest_5", "north", "@@woods_msg");
    add_exit(SHORE + "shore10", "northeast");
    add_exit(SHORE + "shore8", "southwest");
    add_exit(FOREST + "e_forest_3", "west", "@@woods_msg");
}
