#include "defs.h";

inherit TELBERIN_ROOM;

void
create_telberin_room()
{
    add_exit("tel10_15", "north");
    add_exit("tel10_13", "south");
}