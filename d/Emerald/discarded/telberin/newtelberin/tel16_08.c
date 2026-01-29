#include "defs.h";

inherit TELBERIN_ROOM;

void
create_telberin_room()
{
    add_exit("tel16_09", "north");
    add_exit("tel15_07", "southwest");
}