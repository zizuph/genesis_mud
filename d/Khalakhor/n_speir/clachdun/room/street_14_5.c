#include "local.h"

inherit STREET_BASE;

void
create_street()
{
    add_exit(ROOM_DIR + "street_14_4", "north");
    add_exit(ROOM_DIR + "street_14_6", "south");
    add_exit(ROOM_DIR + "building_13_5", "west");
}
