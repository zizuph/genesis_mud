#include "local.h"

inherit BUILDING_BASE;
inherit GUARD_LIB;

void
create_building()
{
    set_guards(2);
    set_up_cords(5,9);
    add_exit(ROOM_DIR + "inn_common", "north");
    add_exit(ROOM_DIR + "street_5_10", "out", out_message);
}
