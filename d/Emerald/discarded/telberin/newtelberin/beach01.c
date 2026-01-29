#include "defs.h";

inherit TELBERIN_ROOM;

void
create_telberin_room()
{
    add_exit("beach02", "east");
    add_exit("beach16", "west");
    add_exit("tel10_19", "south");
}
