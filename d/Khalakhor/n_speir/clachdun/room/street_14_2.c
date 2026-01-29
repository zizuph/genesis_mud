#include "local.h"

inherit STREET_BASE;

void
create_street()
{
    add_exit(ROOM_DIR + "street_14_3", "south");
    add_exit(ROOM_DIR + "building_13_2", "west");
}
