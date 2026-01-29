#include "defs.h"

inherit SHOREBASE;

public void
create_room()
{
    create_shore();
    create_direction("west");

    add_exit(SHORE + "shore24", "north");
    add_exit(FOREST + "w_forest_13", "east", "@@woods_msg");
    add_exit(SHORE + "shore26", "southeast");
}
