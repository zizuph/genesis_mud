#include "local.h"

inherit BUILDING_BASE;

void
create_building()
{
    set_up_cords(5,8);
    add_exit(ROOM_DIR + "inn_kitchen", "east");
    add_exit(ROOM_DIR + "inn_entrance", "south");
    add_exit(ROOM_DIR + "inn_room1", "southwest");
    add_exit(ROOM_DIR + "inn_room2", "west");
}
