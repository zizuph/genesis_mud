#include "local.h"

inherit STREET_BASE;

void
create_street()
{
    add_exit(ROOM_DIR +"street_9_10", "northeast");
    add_exit(ROOM_DIR +"street_8_10", "north");
    add_exit(ROOM_DIR +"street_7_10", "northwest");
    add_exit(ROOM_DIR + "building_8_12", "south");
}
