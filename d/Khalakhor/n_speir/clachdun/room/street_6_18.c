#include "local.h"

inherit STREET_BASE;

void
create_street()
{
    add_exit(ROOM_DIR + "street_7_18", "east");
    add_exit(ROOM_DIR + "street_5_18", "west");
}
