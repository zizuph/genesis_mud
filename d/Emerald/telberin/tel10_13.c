#include "defs.h";

inherit TELBERIN_ROOM;

void
create_telberin_room()
{
    add_exit("tel09_13", "west");
add_exit("tel11_13", "east");
    add_exit("tel10_14", "north");
}