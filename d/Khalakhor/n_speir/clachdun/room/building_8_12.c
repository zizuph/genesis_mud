#include "local.h"

inherit BUILDING_BASE;

void
create_building()
{
    add_exit(ROOM_DIR + "street_8_11", "out", out_message);
    add_exit(ROOM_DIR + "building_9_13", "southeast");
    add_exit(ROOM_DIR + "building_8_13", "south");
    add_exit(ROOM_DIR + "building_7_13", "southwest");
}
