#include "defs.h";

inherit TELBERIN_ROOM;

void
create_telberin_room()
{
    add_exit("tel16_10", "north");
    add_exit("tel16_08", "south");
}