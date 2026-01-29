#pragma strict_types

#include "../hob.h"
inherit HOB_ROOM_SERVER;
#include "hall.h"

public void
hob_room(void)
{
    add_exit(AREA1 + "hall6", "northwest", ran_move, ran_tired);
    add_exit(AREA1 + "hall4", "southeast", ran_move, ran_tired);

    string *dirs = ({ "north", "northeast", "east" });

    if (!random(2))  dirs = ran_exit(AREA1 + "room16", dirs);
    if (!random(4))  dirs = ran_exit(AREA1 + "room17", dirs);

    dirs = ({ "west", "southwest", "south" });

    if (!random(2))  dirs = ran_exit(AREA1 + "room18", dirs);
    if (!random(4))  dirs = ran_exit(AREA1 + "room19", dirs);
}
