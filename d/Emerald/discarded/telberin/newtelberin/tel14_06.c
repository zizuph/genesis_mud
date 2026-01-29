#include "defs.h";

inherit TELBERIN_ROOM;

void
create_telberin_room()
{
    add_exit("tel15_07", "northeast");
    add_exit("tel13_05", "southwest");
    add_exit("tel13_07", "northwest");
}