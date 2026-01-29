#include "local.h"

inherit BUILDING_BASE;

void
create_building()
{
    add_exit(ROOM_DIR + "building_8_13", "north");
    add_exit(ROOM_DIR + "building_9_13", "northeast");
    add_exit(ROOM_DIR + "building_7_13", "northwest");
}
