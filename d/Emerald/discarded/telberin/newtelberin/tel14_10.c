#include "defs.h";

inherit TELBERIN_ROOM;

void
create_telberin_room()
{
    add_exit("tel13_10", "west");
    add_exit("tel15_10", "east");
}