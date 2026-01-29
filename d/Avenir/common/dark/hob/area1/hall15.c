#pragma strict_types

#include "../hob.h"
inherit HOB_ROOM_SERVER;
#include "hall.h"

public void
hob_room(void)
{
    add_exit(AREA1 + "hall14", "northeast", ran_move, ran_tired);
    add_exit(AREA1 + "hall16", "southwest", ran_move, ran_tired);

    string *dirs = ({ "north", "east" });

    if (!random(2))  dirs = ran_exit(AREA1 + "room56", dirs);
    if (!random(4))  dirs = ran_exit(AREA1 + "room57", dirs);

    dirs = ({ "west", "south", "southeast" });

    if (!random(2))  dirs = ran_exit(AREA1 + "room58", dirs);
    if (!random(4))  dirs = ran_exit(AREA1 + "room59", dirs);
}
