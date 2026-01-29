#include "local.h"

inherit BUILDING_BASE;

void
create_building()
{
    add_exit(ROOM_DIR + "blacksmith", "northwest");
    add_exit(ROOM_DIR + "street_14_5", "out", out_message);
}
