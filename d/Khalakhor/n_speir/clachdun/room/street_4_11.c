#include "local.h"

inherit STREET_BASE;

void
create_street()
{
    add_exit(ROOM_DIR + "street_5_10", "northeast");
    add_exit(ROOM_DIR + "building_5_12", "southeast");
    add_exit(ROOM_DIR + "street_3_12", "southwest");
}
