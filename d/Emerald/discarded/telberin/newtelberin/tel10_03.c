#include "defs.h";

inherit TELBERIN_ROOM;

void
create_telberin_room()
{
    add_exit("tel10_04", "north");
    add_exit("tel10_02", "south");
}