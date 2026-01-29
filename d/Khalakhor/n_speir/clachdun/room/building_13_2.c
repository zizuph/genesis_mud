#include "local.h"

inherit BUILDING_BASE;

void
create_building()
{
    add_exit(ROOM_DIR + "bladesmith", "southwest");
    add_exit(ROOM_DIR + "street_14_2", "out", out_message);
}
