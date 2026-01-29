#include "defs.h"

inherit SHOREBASE;

public void
create_room()
{
    create_shore();
    create_direction("south");

    add_prop(ROOM_I_IS_SKIFF_PORT, 1);

    add_exit(FOREST + "s_forest_37", "north", "@@woods_msg");
    add_exit(SHORE + "shore2", "east");
    add_exit(SHORE + "shore32", "west");
}
