#include "local.h"

inherit STREET_BASE;

void
create_street()
{
    add_exit(ROOM_DIR + "street_11_12", "north");
    add_exit(ROOM_DIR + "street_11_14", "south");
    add_exit(ROOM_DIR + "building_10_13", "west");
}
