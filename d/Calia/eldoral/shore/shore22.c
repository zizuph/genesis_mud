#include "defs.h"

inherit SHOREBASE;

public void
create_room()
{
    create_shore();
    create_direction("east");

    add_exit(SHORE + "shore23", "northwest");
    add_exit(SHORE + "shore21", "south");
    add_exit(FOREST + "e_forest_32", "west", "@@woods_msg");
}
