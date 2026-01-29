#include "defs.h"

inherit SHOREBASE;

public void
create_room()
{
    create_shore();
    create_direction("east");

    add_exit(FOREST + "e_forest_22", "north", "@@woods_msg");
    add_exit(SHORE + "shore18", "northeast");
    add_exit(SHORE + "shore16", "southeast");
    add_exit(FOREST + "e_forest_18", "south", "@@woods_msg");
    add_exit(FOREST + "e_forest_20", "west", "@@woods_msg");
}
