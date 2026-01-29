#include "local.h"

inherit BUILDING_BASE;

void
create_building()
{
    add_exit(ROOM_DIR + "building_4_16", "north");
    add_exit(ROOM_DIR + "building_5_17", "east");
}
