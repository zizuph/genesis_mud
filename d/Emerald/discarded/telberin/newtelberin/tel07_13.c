#include "defs.h";

inherit TELBERIN_ROOM;

void
create_telberin_room()
{
    add_exit("tel08_12", "southeast");
    add_exit("tel06_14", "northwest");
}