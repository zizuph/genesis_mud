#include "local.h"

inherit BARRACK_BASE;

void
create_barrack()
{
    add_exit(ROOM_DIR + "barrack_14_15", "northeast");
    add_exit(ROOM_DIR + "barrack_12_17", "southwest");
}
