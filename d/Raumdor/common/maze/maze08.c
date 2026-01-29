#include "defs.h"
inherit MAZE_ROOM;

void
create_room()
{
    ::create_room();
    add_exit("@@lost_exit@@", "north");
    add_exit("@@lost_exit@@", "northeast");
    add_exit("@@true_exit@@", "east");
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
                          "maze02", "maze04", "maze05", "maze07", "maze08",
                          "maze09", "maze03",
                        }));
}

string
true_exit()
{
    if (TP->query_prop(RAUMDOR_AGES_MAZE) == 2)
    {
        TP->add_prop(RAUMDOR_AGES_MAZE, 3);
        return MAZE_DIR + "maze09";
    }
    TP->remove_prop(RAUMDOR_AGES_MAZE);
    return lost_exit();
}
