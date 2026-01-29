#include "local.h"

inherit STREET_BASE;

void
create_street()
{
    add_exit(ROOM_DIR + "building_5_17", "north");
    add_exit(ROOM_DIR + "street_6_18", "east");
}
