#include "defs.h";

inherit TELBERIN_ROOM;

void
create_telberin_room()
{
    add_exit("tel06_14", "northeast");
    add_exit("tel04_12", "southwest");
}