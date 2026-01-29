#include "defs.h";

inherit TELBERIN_ROOM;

void
create_telberin_room()
{
    add_exit("tel07_05", "southeast");
    add_exit("tel05_07", "northwest");
    add_exit("tel07_07", "northeast");
    add_exit("shop", "southwest");
}
