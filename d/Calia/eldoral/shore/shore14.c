#include "defs.h"

inherit SHOREBASE;

public void
create_room()
{
    create_shore();
    create_direction("east");

    add_exit(SHORE + "shore15", "north");
    add_exit(SHORE + "shore13", "southwest");
    add_exit(FOREST + "e_forest_14", "west", "@@woods_msg");
}
