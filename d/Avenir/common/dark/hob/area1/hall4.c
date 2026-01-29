#pragma strict_types

#include "../hob.h"
inherit HOB_ROOM_SERVER;
#include "hall.h"

public void
hob_room(void)
{
    add_exit(AREA1 + "hall5", "northwest", ran_move, ran_tired);
    add_exit(AREA1 + "hall3", "southeast", ran_move, ran_tired);

    string *dirs = ({ "north", "northeast", "east" });

    if (!random(2))  dirs = ran_exit(AREA1 + "room12", dirs);
    if (!random(4))  dirs = ran_exit(AREA1 + "room13", dirs);

    dirs = ({ "west", "southwest", "south" });

    if (!random(2))  dirs = ran_exit(AREA1 + "room14", dirs);
    if (!random(4))  dirs = ran_exit(AREA1 + "room15", dirs);
}
