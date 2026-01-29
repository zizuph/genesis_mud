#include "local.h"

inherit STREET_BASE;

void
create_street()
{
    add_exit(ROOM_DIR + "inn_entrance", "north");
    add_exit(ROOM_DIR + "street_6_10", "east");
    add_exit(ROOM_DIR + "street_4_11", "southwest");
}
