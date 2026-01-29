#include "local.h"

inherit STREET_BASE;
inherit GUARD_LIB;

void
create_street()
{
    set_guards(2);
    add_exit(ROOM_DIR + "building_14_11", "northeast");
    add_exit(ROOM_DIR + "street_14_13", "southeast");
    add_exit(ROOM_DIR + "street_12_11", "northwest");
}
