#include "local.h"

inherit BUILDING_BASE;

void
create_building()
{
    set_up_cords(12,3);
    add_exit(ROOM_DIR + "building_13_2", "northeast");
}
