#include "local.h"

inherit BARRACK_BASE;

void
create_barrack()
{
    add_exit(ROOM_DIR + "barrack_2_13", "north");
    add_exit(ROOM_DIR + "barrack_2_15", "south");
}
