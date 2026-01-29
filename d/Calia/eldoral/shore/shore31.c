#include "defs.h"

inherit SHOREBASE;

public void
create_room()
{
    create_shore();
    create_direction("south");

    add_exit(FOREST + "s_forest_35", "north", "@@north_msg");
    add_exit(SHORE + "shore32", "east");
    add_exit(SHORE + "shore30", "west");
}
