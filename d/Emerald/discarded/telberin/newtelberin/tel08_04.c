#include "defs.h";

inherit TELBERIN_ROOM;

void
create_telberin_room()
{
    add_exit("tel09_04", "east");
    add_exit("tel07_05", "northwest");
}