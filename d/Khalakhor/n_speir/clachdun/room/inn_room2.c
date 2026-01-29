#include "local.h"

inherit BUILDING_BASE;

void
create_building()
{
    set_up_cords(4,8);
    add_exit(ROOM_DIR + "inn_common", "east");
    add_exit(ROOM_DIR + "inn_room1", "south");
}
