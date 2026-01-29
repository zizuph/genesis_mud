#include "local.h"

inherit BUILDING_BASE;

void
create_building()
{
    add_exit(ROOM_DIR + "building_5_16", "north");
    add_exit(ROOM_DIR + "building_6_17", "east");
    add_exit(ROOM_DIR + "building_4_17", "west");
    add_exit(ROOM_DIR + "street_5_18", "out", out_message);
}
