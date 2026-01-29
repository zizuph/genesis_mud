#include "defs.h"

inherit SHOREBASE;

public void
create_room()
{
    create_shore();
    create_direction("south");

    add_exit(FOREST + "s_forest_40", "north", "@@woods_msg");
    add_exit(SHORE + "shore5", "northeast");
    add_exit(SHORE + "shore3", "west");
}
