#include "local.h"

inherit BARRACK_BASE;
inherit GUARD_LIB;

void
create_barrack()
{
    set_guards(3);
    add_exit(ROOM_DIR + "barrack_16_13", "northeast");
    add_exit(ROOM_DIR + "barrack_14_15", "southwest");
    add_exit(ROOM_DIR + "street_14_13", "northwest");
    add_exit(FOREST_DIR + "path_16_15", "southeast");
}
