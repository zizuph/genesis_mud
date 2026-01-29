#include "defs.h"

inherit SHOREBASE;

public void
create_room()
{
    create_shore();
    create_direction("east");

    add_exit(SHORE + "shore21", "northwest");
    add_exit(SHORE + "shore19", "south");
    add_exit(FOREST + "e_forest_28", "west", "@@woods_msg");
}
