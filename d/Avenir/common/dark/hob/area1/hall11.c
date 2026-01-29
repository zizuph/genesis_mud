#pragma strict_types

#include "../hob.h"
inherit HOB_ROOM_SERVER;
#include "hall.h"

public void
hob_room(void)
{
    add_exit(AREA1 + "hall10", "west", ran_move, ran_tired);
    add_exit(AREA1 + "hall12", "east", ran_move, ran_tired);

    string *dirs = ({ "northwest", "north", "northeast" });

    if (!random(2))  dirs = ran_exit(AREA1 + "room40", dirs);
    if (!random(4))  dirs = ran_exit(AREA1 + "room41", dirs);

    dirs = ({ "southwest", "south", "southeast" });

    if (!random(2))  dirs = ran_exit(AREA1 + "room42", dirs);
    if (!random(4))  dirs = ran_exit(AREA1 + "room43", dirs);
}
