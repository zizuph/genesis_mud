#include "defs.h";

inherit TELBERIN_ROOM;

void
create_telberin_room()
{
    add_exit("tel10_18", "south");
    add_exit("beach/beach01", "north");
}
