#include "local.h"

inherit BUILDING_BASE;

void
create_building()
{
    add_exit(ROOM_DIR + "building_8_12", "north");
    add_exit(ROOM_DIR + "building_9_13", "east");
    add_exit(ROOM_DIR + "building_8_14", "south");
    add_exit(ROOM_DIR + "building_7_13", "west");
    add_exit(ROOM_DIR + "tower_lv1", "up");
}
