#include "defs.h";

inherit TELBERIN_ROOM;

void
create_telberin_room()
{
    add_exit("tel05_07", "southeast");
    add_exit("tel04_09", "north");
}