#include "defs.h";

inherit TELBERIN_ROOM;

void
create_telberin_room()
{
    add_exit("tel10_16", "north");
    add_exit("tel10_14", "south");
}