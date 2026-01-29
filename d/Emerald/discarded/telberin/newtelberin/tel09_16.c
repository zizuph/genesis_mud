#include "defs.h";

inherit TELBERIN_ROOM;

void
create_telberin_room()
{
    add_exit("tel08_16", "west");
    add_exit("tel10_16", "east");
}