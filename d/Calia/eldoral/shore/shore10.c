#include "defs.h"

inherit SHOREBASE;

public void
create_room()
{
    create_shore();
    create_direction("east");

    add_exit(SHORE + "shore11", "north");
    add_exit(SHORE + "shore9", "southwest");
    add_exit(FOREST + "e_forest_5", "west", "@@woods_msg");
}
