#include "defs.h";

inherit TELBERIN_ROOM;

void
create_telberin_room()
{
    add_exit("tel16_11", "north");
    add_exit("tel16_09", "south");
    add_exit("tel15_10", "west");
    add_exit("tel17_10", "east");
}