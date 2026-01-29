#include "defs.h"

inherit SHOREBASE;

public void
create_room()
{
    create_shore();
    create_direction("south");

    add_exit(FOREST + "s_forest_39", "north", "@@woods_msg");
    add_exit(SHORE + "shore4", "east");
    add_exit(SHORE + "shore2", "west");
}
