#include "local.h"

inherit STREET_BASE;

void
create_street()
{
    add_exit(ROOM_DIR + "street_11_13", "north");
    add_exit(ROOM_DIR + "street_10_15", "southwest");
}
