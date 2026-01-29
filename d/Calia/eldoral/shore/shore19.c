#include "defs.h"

inherit SHOREBASE;

public void
create_room()
{
    create_shore();
    create_direction("east");

    add_exit(SHORE + "shore20", "north");
    add_exit(SHORE + "shore18", "south");
    add_exit(FOREST + "e_forest_25", "west", "@@woods_msg");
}
