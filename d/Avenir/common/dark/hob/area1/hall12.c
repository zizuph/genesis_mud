#pragma strict_types

#include "../hob.h"
inherit HOB_ROOM_SERVER;
#include "hall.h"

public void
hob_room(void)
{
    add_exit(AREA1 + "hall11", "west", ran_move, ran_tired);
    add_exit(AREA1 + "hall13", "southeast", ran_move, ran_tired);

    string *dirs = ({ "north", "northeast" });

    if (!random(2))  dirs = ran_exit(AREA1 + "room44", dirs);
    if (!random(4))  dirs = ran_exit(AREA1 + "room45", dirs);

    dirs = ({ "south", "southwest", });

    if (!random(2))  dirs = ran_exit(AREA1 + "room46", dirs);
    if (!random(4))  dirs = ran_exit(AREA1 + "room47", dirs);
}
