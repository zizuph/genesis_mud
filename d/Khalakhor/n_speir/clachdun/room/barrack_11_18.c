#include "local.h"

inherit BARRACK_BASE;
inherit GUARD_LIB;

void
create_barrack()
{
    set_guards(1);
    add_exit(ROOM_DIR + "barrack_12_17", "northeast");
}
