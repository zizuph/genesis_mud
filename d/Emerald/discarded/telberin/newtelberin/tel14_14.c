#include "defs.h";

inherit TELBERIN_ROOM;

void
create_telberin_room()
{
    add_exit("tel13_15", "northwest");
    add_exit("tel15_13", "southeast");
    add_exit("tel13_13", "southwest");
}