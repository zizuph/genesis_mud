#include "defs.h"

inherit SHOREBASE;

public void
create_room()
{
    create_shore();
    create_direction("east");

    add_exit(SHORE + "shore17", "northwest");
    add_exit(SHORE + "shore15", "south");
    add_exit(FOREST + "e_forest_18", "west", "@@woods_msg");
}
