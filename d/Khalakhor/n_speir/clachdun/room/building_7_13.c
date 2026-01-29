#include "local.h"

inherit BUILDING_BASE;

void
create_building()
{
    add_exit(ROOM_DIR + "building_8_12", "northeast");
    add_exit(ROOM_DIR + "building_8_13", "east");
    add_exit(ROOM_DIR + "building_8_14", "southeast");
}
