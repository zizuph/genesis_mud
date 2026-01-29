#include "defs.h"

inherit SHOREBASE;

public void
create_room()
{
    create_shore();
    create_direction("east");

    add_exit(SHORE + "shore22", "north");
    add_exit(SHORE + "shore20", "southeast");
    add_exit(FOREST + "e_forest_28", "south", "@@woods_msg");
    add_exit(FOREST + "e_forest_30", "west", "@@woods_msg");
}
