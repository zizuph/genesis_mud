#include "local.h"

inherit STREET_BASE;

void
create_street()
{
    add_exit(ROOM_DIR +"street_8_11", "southeast");
    add_exit(ROOM_DIR +"street_8_10", "east");
    add_exit(ROOM_DIR +"street_8_9", "northeast");
    add_exit(ROOM_DIR +"street_6_10", "west");
}
