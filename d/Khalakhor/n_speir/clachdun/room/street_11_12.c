#include "local.h"

inherit STREET_BASE;
inherit GUARD_LIB;

void
create_street()
{
    set_guards(2);
    add_exit(ROOM_DIR + "street_11_11", "north");
    add_exit(ROOM_DIR + "building_12_12", "east");
    add_exit(ROOM_DIR + "street_11_13", "south");
}
