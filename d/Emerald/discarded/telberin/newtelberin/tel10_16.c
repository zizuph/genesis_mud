#include "defs.h";

inherit TELBERIN_ROOM;

void
create_telberin_room()
{
    add_exit("tel09_16", "west");
    add_exit("tel10_15", "south");
    add_exit("tel11_16", "east");
    add_exit("tel10_17", "north");
}