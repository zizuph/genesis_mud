#include "defs.h";

inherit TELBERIN_ROOM;

void
create_telberin_room()
{
    add_exit("tel16_12", "north");
    add_exit("tel16_10", "south");
}