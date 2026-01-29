#include "defs.h";

inherit TELBERIN_ROOM;

void
create_telberin_room()
{
    add_exit("tel08_08", "southeast");
    add_exit("tel07_10", "north");
}