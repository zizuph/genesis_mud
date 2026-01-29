#pragma strict_types

#include "../hob.h"
inherit HOB_ROOM_SERVER;
#include "hall.h"

public void
hob_room(void)
{
    add_exit(AREA1 + "hall9", "east", ran_move, ran_tired);
    add_exit(AREA1 + "hall7", "west", ran_move, ran_tired);

    string *dirs = ({ "northwest", "north", "northeast" });

    if (!random(2))  dirs = ran_exit(AREA1 + "room28", dirs);
    if (!random(4))  dirs = ran_exit(AREA1 + "room29", dirs);

    dirs = ({ "southwest", "south", "southeast" });

    if (!random(2))  dirs = ran_exit(AREA1 + "room30", dirs);
    if (!random(4))  dirs = ran_exit(AREA1 + "room31", dirs);
}
