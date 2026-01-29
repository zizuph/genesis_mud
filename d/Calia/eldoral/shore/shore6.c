#include "defs.h"

inherit SHOREBASE;

public void
create_room()
{
    create_shore();
    create_direction("south");

    add_exit(FOREST + "s_forest_25", "north", "@@woods_msg");
    add_exit(SHORE + "shore7", "northeast");
    add_exit(SHORE + "shore5", "southwest");
    add_exit(FOREST + "s_forest_33", "west", "@@woods_msg");
}
