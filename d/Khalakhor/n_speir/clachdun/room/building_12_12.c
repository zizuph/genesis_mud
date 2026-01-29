#include "local.h"

inherit BUILDING_BASE;

void
create_building()
{
    add_exit(ROOM_DIR + "street_11_12", "out", out_message);
}
