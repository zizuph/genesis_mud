#include "defs.h"

inherit SHOREBASE;

public void
create_room()
{
    create_shore();
    create_direction("south");

    add_exit(FOREST + "s_forest_33", "north", "@@woods_msg");
    add_exit(SHORE + "shore6", "northeast");
    add_exit(SHORE + "shore4", "southwest");
    add_exit(FOREST + "s_forest_40", "west", "@@woods_msg");
}
