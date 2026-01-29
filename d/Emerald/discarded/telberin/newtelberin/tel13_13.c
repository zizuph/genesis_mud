#include "defs.h";

inherit TELBERIN_ROOM;

void
create_telberin_room()
{
    add_exit("tel14_14", "northeast");
    add_exit("tel12_12", "southwest");
}