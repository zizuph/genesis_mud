#pragma strict_types

#include "../hob.h"
inherit HOB_ROOM_SERVER;
#include "hall.h"

public void
hob_room(void)
{
    add_exit(AREA1 + "hall12", "northwest", ran_move, ran_tired);
    add_exit(AREA1 + "hall14", "southwest", ran_move, ran_tired);

    string *dirs = ({ "north", "east" });

    if (!random(2))  dirs = ran_exit(AREA1 + "room48", dirs);
    if (!random(4))  dirs = ran_exit(AREA1 + "room49", dirs);

    dirs = ({ "west", "south", });

    if (!random(2))  dirs = ran_exit(AREA1 + "room50", dirs);
    if (!random(4))  dirs = ran_exit(AREA1 + "room51", dirs);
}
