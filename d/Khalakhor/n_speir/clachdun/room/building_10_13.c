#include "local.h"

inherit BUILDING_BASE;

void
create_building()
{
    add_exit(ROOM_DIR + "building_10_12", "north");
    add_exit(ROOM_DIR + "street_11_13", "out", out_message);
}
