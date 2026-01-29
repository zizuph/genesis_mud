#include "local.h"

inherit BARRACK_BASE;
inherit GUARD_LIB;

void
create_barrack()
{
    set_guards(3);
    add_exit(ROOM_DIR + "barrack_8_8", "west");
}
