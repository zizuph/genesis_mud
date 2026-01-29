#include "defs.h";

inherit TELBERIN_ROOM;

void
create_telberin_room()
{
    add_exit("tel11_13", "northwest");
add_exit("tel13_11", "southeast");
    add_exit("tel13_13", "northeast");
}