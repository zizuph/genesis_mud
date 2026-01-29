#include "defs.h"
inherit MAZE_ROOM;

void
create_room()
{
    ::create_room();
    add_exit("@@lost_exit@@", "north");
    add_exit("@@lost_exit@@", "northeast");
    add_exit("@@lost_exit@@", "east");
    add_exit("@@lost_exit@@", "southeast");
    add_exit("@@lost_exit@@", "south");
    add_exit("@@lost_exit@@", "southwest");
    add_exit("@@lost_exit@@", "west");
    add_exit("@@lost_exit@@", "northwest");
}

string
lost_exit()
{
    TP->remove_prop(RAUMDOR_AGES_MAZE);
    return MAZE_DIR + one_of_list(({
                          "maze02", "maze06", "maze05", "maze07", "maze08",
                          "maze09", "maze03",
                        }));
}
