#include "local.h"

inherit STREET_BASE;

void
create_street()
{
    add_exit(ROOM_DIR +"street_4_11", "northeast");
    add_exit(ROOM_DIR +"barrack_2_12", "west");
}
