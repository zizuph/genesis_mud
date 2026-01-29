#include "defs.h";

inherit TELBERIN_ROOM;

void
create_telberin_room()
{
    add_exit("tel09_07", "southeast");
add_exit("tel07_09", "northwest");
    add_exit("tel07_07", "southwest");
}