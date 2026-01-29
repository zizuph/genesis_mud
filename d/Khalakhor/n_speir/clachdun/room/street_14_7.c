#include "local.h"

inherit STREET_BASE;

void
create_street()
{
    add_exit(ROOM_DIR + "street_13_8", "southwest");
    add_exit(ROOM_DIR + "street_14_6", "north");
}
