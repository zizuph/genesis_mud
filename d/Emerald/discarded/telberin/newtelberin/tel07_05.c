#include "defs.h";

inherit TELBERIN_ROOM;

void
create_telberin_room()
{
    add_exit("tel08_04", "southeast");
    add_exit("tel06_06", "northwest");
    add_exit("armoury", "southwest");
}
