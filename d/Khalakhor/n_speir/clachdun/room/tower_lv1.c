#include "local.h"

inherit BUILDING_BASE;

void
create_building()
{
    // No z co-ordinate so we keep the same x and y
    set_up_cords(8,13);
    add_exit(ROOM_DIR + "tower_lv2", "up");
    add_exit(ROOM_DIR + "building_8_13", "down");
}
