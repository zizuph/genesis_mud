#include "defs.h";

inherit TELBERIN_ROOM;

void
create_telberin_room()
{
    add_exit("tel07_11", "southwest");
add_exit("tel09_13", "northeast");
    add_exit("tel07_13", "northwest");
}