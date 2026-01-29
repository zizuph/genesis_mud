#include "local.h"

inherit STREET_BASE;

void
create_street()
{
    add_exit(ROOM_DIR + "street_14_2", "north");
    add_exit(ROOM_DIR + "street_14_4", "south");
}
