#include "local.h"

inherit BUILDING_BASE;

void
create_building()
{
    add_exit(ROOM_DIR + "street_9_16", "out", out_message);
    add_exit(ROOM_DIR + "bank", "southwest");
}
