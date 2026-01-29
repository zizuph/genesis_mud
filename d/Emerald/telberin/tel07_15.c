#include "defs.h";

inherit TELBERIN_ROOM;

void
create_telberin_room()
{
    add_exit("tel06_14", "southwest");
    add_exit("tel08_16", "northeast");
}