#include "defs.h"

inherit SHOREBASE;

public void
create_room()
{
    create_shore();
    create_direction("south");

    add_exit(FOREST + "e_forest_1", "north", "@@woods_msg");
    add_exit(SHORE + "shore8", "northeast");
    add_exit(SHORE + "shore6", "southwest");
    add_exit(FOREST + "s_forest_25", "west", "@@woods_msg");

}
