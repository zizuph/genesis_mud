#include "defs.h"

inherit SHOREBASE;

public void
create_room()
{
    create_shore();
    create_direction("west");

    add_exit(FOREST + "w_forest_14", "north", "@@woods_msg");
    add_exit(FOREST + "s_forest_18", "east", "@@woods_msg");
    add_exit(SHORE + "shore28", "southeast");
    add_exit(SHORE + "shore26", "west");
}
