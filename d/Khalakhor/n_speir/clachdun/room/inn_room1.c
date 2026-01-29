#include "local.h"

inherit BUILDING_BASE;

void
create_building()
{
    set_up_cords(4,9);
    add_exit(ROOM_DIR + "inn_room2", "north");
    add_exit(ROOM_DIR + "inn_common", "northeast");
}
