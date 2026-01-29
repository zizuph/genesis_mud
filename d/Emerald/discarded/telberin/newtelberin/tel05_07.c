#include "defs.h";

inherit TELBERIN_ROOM;

void
create_telberin_room()
{
    add_exit("tel06_06", "southeast");
    add_exit("tel04_08", "northwest");
}