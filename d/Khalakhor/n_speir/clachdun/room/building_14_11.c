#include "local.h"

inherit BUILDING_BASE;

void
create_building()
{
    add_exit(ROOM_DIR + "building_13_10", "northwest");
    add_exit(ROOM_DIR + "street_13_12", "out", out_message);
}
