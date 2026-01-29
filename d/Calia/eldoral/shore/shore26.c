#include "defs.h"

inherit SHOREBASE;

public void
create_room()
{
    create_shore();
    create_direction("west");

    add_exit(FOREST + "w_forest_13", "north", "@@woods_msg");
    add_exit(SHORE + "shore27", "east");
    add_exit(SHORE + "shore25", "northwest");
}
