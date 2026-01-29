#include "local.h"

inherit BUILDING_BASE;

void
create_building()
{
    add_exit(ROOM_DIR + "building_5_16", "east");
    add_exit(ROOM_DIR + "building_4_17", "south");
}
