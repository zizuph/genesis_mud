#include "defs.h";

inherit TELBERIN_ROOM;

void
create_telberin_room()
{
    add_exit("tel11_04", "east");
    add_exit("tel09_04", "west");
    add_exit("tel10_05", "north");
    add_exit("tel10_03", "south");
}