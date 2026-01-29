#pragma strict_types

#include "../hob.h"
inherit HOB_ROOM_SERVER;
#include "hall.h"

public void
hob_room(void)
{
    add_exit(AREA1 + "hall9",  "west", ran_move, ran_tired);
    add_exit(AREA1 + "hall11", "east", ran_move, ran_tired);

    string *dirs = ({ "northwest", "north", "northeast" });

    if (!random(2))  dirs = ran_exit(AREA1 + "room36", dirs);
    if (!random(4))  dirs = ran_exit(AREA1 + "room37", dirs);

    dirs = ({ "southwest", "south", "southeast" });

    if (!random(2))  dirs = ran_exit(AREA1 + "room38", dirs);
    if (!random(4))  dirs = ran_exit(AREA1 + "room39", dirs);
}
