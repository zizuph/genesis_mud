#include "local.h"

inherit BARRACK_BASE;

void
create_barrack()
{
    add_exit(ROOM_DIR +"barrack_2_7", "north");
    add_exit(ROOM_DIR +"barrack_2_9", "south");
}
