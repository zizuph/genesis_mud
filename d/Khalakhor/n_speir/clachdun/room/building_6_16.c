#include "local.h"

inherit BUILDING_BASE;

void
create_building()
{
    add_exit(ROOM_DIR + "building_6_17", "south");
    add_exit(ROOM_DIR + "building_5_16", "west");
}
