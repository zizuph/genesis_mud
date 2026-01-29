#include "local.h"

inherit STREET_BASE;

void
create_street()
{
    add_exit(ROOM_DIR + "barrack_8_8", "north");
    add_exit(ROOM_DIR + "street_8_10", "south");
    add_exit(ROOM_DIR + "street_9_10", "southeast");
    add_exit(ROOM_DIR + "street_7_10", "southwest");
}
