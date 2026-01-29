#include "defs.h";

inherit TELBERIN_ROOM;

void
create_telberin_room()
{
    add_exit("tel04_08", "south");
    add_exit("tel04_10", "north");
    add_exit("post", "west");
}
