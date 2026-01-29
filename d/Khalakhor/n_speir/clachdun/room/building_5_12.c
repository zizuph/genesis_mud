#include "local.h"

inherit BUILDING_BASE;

void
create_building()
{
    add_exit(ROOM_DIR + "store", "east");
    add_exit(ROOM_DIR + "post_office", "south");
    add_exit(ROOM_DIR + "street_4_11", "out", out_message);
}
