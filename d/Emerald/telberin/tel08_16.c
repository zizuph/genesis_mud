#include "defs.h";

inherit TELBERIN_ROOM;

void
create_telberin_room()
{
    add_exit("tel07_15", "southwest");
    add_exit("tel09_16", "east");
}