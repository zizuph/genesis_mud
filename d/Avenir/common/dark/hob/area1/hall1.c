#pragma strict_types

#include "../hob.h"
inherit HOB_ROOM_SERVER;
#include "hall.h"

public void
hob_room(void)
{
    add_exit(AREA1 + "hall2", "northwest", ran_move, ran_tired);
    add_exit(HOB + "guard_room", "southeast", ran_move, ran_tired);

    string *dirs = ({ "north", });

    if (!random(3))  ran_exit(AREA1 + "room1", ({ "north" }));

    dirs = ({ "west", "southwest" });

    if (!random(2))  dirs = ran_exit(AREA1 + "room2", dirs);
    if (!random(4))  dirs = ran_exit(AREA1 + "room3", dirs);
}
