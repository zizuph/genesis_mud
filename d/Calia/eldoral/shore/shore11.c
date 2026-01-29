#include "defs.h"

inherit SHOREBASE;

public void
create_room()
{
    create_shore();
    create_direction("east");

    add_exit(SHORE + "shore12", "northwest");
    add_exit(SHORE + "shore10", "south");
    add_exit(FOREST + "e_forest_7", "west", "@@woods_msg");
}
