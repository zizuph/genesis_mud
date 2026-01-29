#include "defs.h"

inherit SHOREBASE;

public void
create_room()
{
    create_shore();
    create_direction("east");

    add_exit(SHORE + "shore19", "north");
    add_exit(SHORE + "shore17", "southwest");
    add_exit(FOREST + "e_forest_22", "west", "@@woods_msg");
}
