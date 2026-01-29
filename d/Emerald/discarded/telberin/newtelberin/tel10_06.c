#include "defs.h";

inherit TELBERIN_ROOM;

void
create_telberin_room()
{
    add_exit("tel10_05", "south");
    add_exit("tel10_07", "north");
}