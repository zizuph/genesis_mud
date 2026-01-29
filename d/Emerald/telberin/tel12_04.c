#include "defs.h";

inherit TELBERIN_ROOM;

void
create_telberin_room()
{
    add_exit("tel13_05", "northeast");
    add_exit("tel11_04", "west");
}