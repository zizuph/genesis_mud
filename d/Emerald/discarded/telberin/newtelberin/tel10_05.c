#include "defs.h";

inherit TELBERIN_ROOM;

void
create_telberin_room()
{
    add_exit("tel10_04", "south");
    add_exit("tel10_06", "north");
}