#pragma strict_types

#include "../hob.h"
inherit HOB_ROOM_SERVER;
#include "hall.h"

public void
hob_room(void)
{
    add_exit(AREA1 + "hall17", "northeast", ran_move, ran_tired);
    add_exit(HOB + "guard_room", "southwest", ran_move, ran_tired);

    string *dirs = ({ "north", });

    if (!random(3))  dirs = ran_exit(AREA1 + "room68", dirs);

    dirs = ({ "east", "southeast" });

    if (!random(2))  dirs = ran_exit(AREA1 + "room69", dirs);
    if (!random(4))  dirs = ran_exit(AREA1 + "room70", dirs);
}
