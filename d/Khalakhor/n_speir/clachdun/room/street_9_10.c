#include "local.h"

inherit STREET_BASE;

void
create_street()
{
    add_exit(ROOM_DIR + "street_10_10", "east");
    add_exit(ROOM_DIR + "street_8_11", "southwest");
    add_exit(ROOM_DIR + "street_8_10", "west");
    add_exit(ROOM_DIR + "street_8_9", "northwest");
}
