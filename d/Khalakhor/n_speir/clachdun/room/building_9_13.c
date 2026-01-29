#include "local.h"

inherit BUILDING_BASE;

void
create_building()
{
    add_exit(ROOM_DIR + "building_8_14", "southwest");
    add_exit(ROOM_DIR + "building_8_13", "west");
    add_exit(ROOM_DIR + "building_8_12", "northwest");
}
