#include "defs.h";

inherit TELBERIN_ROOM;

void
create_telberin_room()
{
    add_exit("tel04_12", "north");
    add_exit("tel04_10", "south");
}