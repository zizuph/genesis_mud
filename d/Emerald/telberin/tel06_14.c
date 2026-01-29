#include "defs.h";

inherit TELBERIN_ROOM;

void
create_telberin_room()
{
    add_exit("tel07_13", "southeast");
    add_exit("tel05_13", "southwest");
    add_exit("tel07_15", "northeast");
}