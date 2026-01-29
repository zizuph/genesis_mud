#include "local.h"

inherit STREET_BASE;

void
create_street()
{
    add_exit(ROOM_DIR + "street_11_14", "northeast");
    add_exit(ROOM_DIR + "street_9_16", "southwest");
}
