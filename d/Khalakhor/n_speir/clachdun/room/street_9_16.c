#include "local.h"

inherit STREET_BASE;

void
create_street()
{
    add_exit(ROOM_DIR + "street_10_15", "northeast");
    add_exit(ROOM_DIR + "street_8_17", "southwest");
    add_exit(ROOM_DIR + "building_8_15", "northwest");
}
