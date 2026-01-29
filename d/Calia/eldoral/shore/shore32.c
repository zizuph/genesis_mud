#include "defs.h"

inherit SHOREBASE;

public void
create_room()
{
    create_shore();
    create_direction("south");

    add_exit(FOREST + "s_forest_36", "north","@@woods_msg");
    add_exit(SHORE + "shore1", "east");
    add_exit(SHORE + "shore31", "west");
}
