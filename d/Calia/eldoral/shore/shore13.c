#include "defs.h"

inherit SHOREBASE;

public void
create_room()
{
    create_shore();
    create_direction("east");

    add_exit(FOREST + "e_forest_14", "north", "@@woods_msg");
    add_exit(SHORE + "shore14", "northeast");
    add_exit(SHORE + "shore12", "south");
    add_exit(FOREST + "e_forest_11", "west", "@@woods_msg");
}
