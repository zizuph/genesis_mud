#include "local.h"

inherit BARRACK_BASE;
inherit GUARD_LIB;

void
create_barrack()
{
    set_guards(2);
    add_exit(ROOM_DIR + "barrack_16_13", "southwest");
}
