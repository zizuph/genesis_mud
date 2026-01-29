#pragma strict_types

#include "../hob.h"
inherit HOB_ROOM_SERVER;
#include "hall.h"

public void
hob_room(void)
{
    add_exit(AREA1 + "hall7", "northeast", ran_move, ran_tired);
    add_exit(AREA1 + "hall5", "southeast", ran_move, ran_tired);

    string *dirs = ({ "north", "northwest", "east" });

    if (!random(2))  dirs = ran_exit(AREA1 + "room20", dirs);
    if (!random(4))  dirs = ran_exit(AREA1 + "room21", dirs);

    dirs = ({ "west", "southwest", "south" });

    if (!random(2))  dirs = ran_exit(AREA1 + "room22", dirs);
    if (!random(4))  dirs = ran_exit(AREA1 + "room23", dirs);
}
