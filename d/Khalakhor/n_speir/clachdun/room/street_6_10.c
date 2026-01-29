#include "local.h"

inherit STREET_BASE;

void
create_street()
{
    add_exit(ROOM_DIR + "street_7_10", "east");
    add_exit(ROOM_DIR + "street_5_10", "west");
}
