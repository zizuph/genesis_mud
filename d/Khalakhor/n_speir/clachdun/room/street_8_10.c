#include "local.h"

inherit STREET_BASE;
inherit GUARD_LIB;

void
create_street()
{
    set_guards(4);
    add_exit(ROOM_DIR + "street_8_9", "north");
    add_exit(ROOM_DIR +"street_9_10", "east");
    add_exit(ROOM_DIR + "street_8_11", "south");
    add_exit(ROOM_DIR + "street_7_10", "west");
}
