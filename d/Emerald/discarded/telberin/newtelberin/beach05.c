#include "defs.h";

inherit TELBERIN_ROOM;

void
create_telberin_room()
{
    add_exit("beach06", "south");
    add_exit("beach04", "north");
    add_exit("tel19_10", "west");
}
