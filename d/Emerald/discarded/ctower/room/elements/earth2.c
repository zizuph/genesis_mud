#include "../../ctower.h"

inherit EARTHSTD;

void
create_earth()
{
    add_exit(CTOWER_ROOM_ELEM + "water2", "south");
    add_exit(CTOWER_ROOM_ELEM + "earth3", "southwest");
    add_exit(CTOWER_ROOM_ELEM + "earth4", "southeast");
}
