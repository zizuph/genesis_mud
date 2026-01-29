#include "defs.h"

inherit SHOREBASE;

public void
create_room()
{
    create_shore();
    create_direction("south");

    add_exit(FOREST + "s_forest_18", "north", "@@woods_msg");
    add_exit(FOREST + "s_forest_26", "east", "@@woods_msg");
    add_exit(SHORE + "shore29", "southeast");
    add_exit(SHORE + "shore27", "northwest");
}
