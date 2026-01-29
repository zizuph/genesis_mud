#include "local.h"

inherit STREET_BASE;

void
create_street()
{
    add_exit(ROOM_DIR + "street_13_12", "southeast");
    add_exit(ROOM_DIR + "street_11_10", "northwest");
}
