#include "defs.h";

inherit TELBERIN_ROOM;

void
create_telberin_room()
{
    add_exit("tel10_03", "north");
    add_exit("tel10_01", "south");
}