#include "defs.h";

inherit TELBERIN_ROOM;

void
create_telberin_room()
{
    add_exit("beach10", "west");
    add_exit("beach08", "east");
    add_exit("tel10_01", "north");
}
