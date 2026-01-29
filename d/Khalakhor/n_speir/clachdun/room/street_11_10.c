#include "local.h"

inherit STREET_BASE;

void
create_street()
{
    add_exit(ROOM_DIR + "street_12_9", "northeast");
    add_exit(ROOM_DIR + "street_12_11", "southeast");
    add_exit(ROOM_DIR + "street_11_11", "south");
    add_exit(ROOM_DIR + "street_10_10", "west");
}
