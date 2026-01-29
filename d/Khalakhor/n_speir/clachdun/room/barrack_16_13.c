#include "local.h"

inherit BARRACK_BASE;
inherit GUARD_LIB;

void
create_barrack()
{
    set_guards(4);
    add_exit(ROOM_DIR + "barrack_17_12", "northeast");
    add_exit(ROOM_DIR + "barrack_15_14", "southwest");
}
