#pragma strict_types

#include "../hob.h"
inherit HOB_ROOM_SERVER;
#include "hall.h"

public void
hob_room(void)
{
    add_exit(AREA1 + "hall8", "east", ran_move, ran_tired);
    add_exit(AREA1 + "hall6", "southwest", ran_move, ran_tired);

    string *dirs = ({ "north", "northwest" });

    if (!random(2))  dirs = ran_exit(AREA1 + "room24", dirs);
    if (!random(4))  dirs = ran_exit(AREA1 + "room25", dirs);

    dirs = ({ "west", "south" });

    if (!random(2))  dirs = ran_exit(AREA1 + "room26", dirs);
    if (!random(4))  dirs = ran_exit(AREA1 + "room27", dirs);
}
