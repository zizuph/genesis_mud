#include "defs.h";

inherit TELBERIN_ROOM;

void
create_telberin_room()
{
    add_exit("tel16_08", "northeast");
    add_exit("tel14_06", "southwest");
}