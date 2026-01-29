#include "local.h"

inherit BARRACK_BASE;
inherit GUARD_LIB;

void
create_barrack()
{
    set_guards(3);
    add_exit(ROOM_DIR + "barrack_9_8", "east");
    add_exit(ROOM_DIR + "street_8_9", "south");
    add_exit(ROOM_DIR + "barrack_7_8", "west");
}
