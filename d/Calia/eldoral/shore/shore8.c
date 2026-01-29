#include "defs.h"

inherit SHOREBASE;

public void
create_room()
{
    create_shore();
    create_direction("south");

    add_exit(FOREST + "e_forest_3", "north", "@@woods_msg");
    add_exit(SHORE + "shore9", "northeast");
    add_exit(SHORE + "shore7", "southwest");
    add_exit(FOREST + "e_forest_1", "west", "@@woods_msg");
}
