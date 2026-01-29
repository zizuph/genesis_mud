#include "local.h"

inherit BARRACK_BASE;

void
create_barrack()
{
    add_exit(ROOM_DIR + "barrack_2_14", "north");
    add_exit(ROOM_DIR + "barrack_2_16", "south");
}
