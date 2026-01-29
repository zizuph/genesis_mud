#include "defs.h";

inherit TELBERIN_ROOM;

void
create_telberin_room()
{
    add_exit("tel13_09", "northeast");
add_exit("tel11_07", "southwest");
    add_exit("tel13_07", "southeast");
}