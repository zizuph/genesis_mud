#include "defs.h";

inherit TELBERIN_ROOM;

void
create_telberin_room()
{
    add_exit("tel05_13", "northeast");
    add_exit("tel04_11", "south");
}