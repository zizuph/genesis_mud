#include "local.h"

inherit BUILDING_BASE;

void
create_building()
{
    set_up_cords(6,12);
    add_exit(ROOM_DIR + "store", "down");
}
