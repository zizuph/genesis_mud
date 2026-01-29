#include "defs.h"

inherit SHOREBASE;

public void
create_room()
{
    create_shore();
    create_direction("east");

    add_exit(SHORE + "shore13", "north");
    add_exit(SHORE + "shore11", "southeast");
    add_exit(FOREST + "e_forest_7", "south", "@@woods_msg");
    add_exit(FOREST + "e_forest_9", "west", "@@woods_msg");
}
