#include "defs.h";

inherit TELBERIN_ROOM;

void
create_telberin_room()
{
    add_exit("tel08_08", "northeast");
    add_exit("tel06_06", "southwest");
}