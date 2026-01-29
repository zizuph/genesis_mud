#include "defs.h";

inherit TELBERIN_ROOM;

void
create_telberin_room()
{
    add_exit("tel12_04", "east");
    add_exit("tel10_04", "west");
}