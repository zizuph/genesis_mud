#include "local.h"

inherit STREET_BASE;

void
create_street()
{
    add_exit(ROOM_DIR + "street_8_17", "northeast");
    add_exit(ROOM_DIR + "street_6_18", "west");
}
