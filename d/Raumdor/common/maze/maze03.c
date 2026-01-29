#include "defs.h"
inherit MAZE_ROOM;

void
create_room()
{
    suffix = " There is an opening to the south.";
    ::create_room();
    add_item("opening", "It looks like the way out.\n");
    add_exit("@@true_exit@@", "north");
    add_exit("@@lost_exit@@", "northeast");
    add_exit("@@lost_exit@@", "east");
    add_exit(MAZE_DIR + "maze01", "south");
    add_exit("@@lost_exit@@", "west");
    add_exit("@@lost_exit@@", "northwest");
}

string
lost_exit()
{
    TP->remove_prop(RAUMDOR_AGES_MAZE);
    return MAZE_DIR + one_of_list(({
                          "maze02", "maze05", "maze07", "maze04",
                        }));
}

string
true_exit()
{
    TP->add_prop(RAUMDOR_AGES_MAZE, 1);
    return MAZE_DIR + "maze06";
}
