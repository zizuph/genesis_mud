#pragma strict_types

#include "../hob.h"
inherit HOB_ROOM_SERVER;
#include "hall.h"

public void
hob_room(void)
{
    add_exit(AREA1 + "hall16", "northeast", ran_move, ran_tired);
    add_exit(AREA1 + "hall18", "southwest", ran_move, ran_tired);

    string *dirs = ({ "north", "east" });

    if (!random(2))  dirs = ran_exit(AREA1 + "room64", dirs);
    if (!random(4))  dirs = ran_exit(AREA1 + "room65", dirs);

    dirs = ({ "west", "south", "southeast" });

    if (!random(2))  dirs = ran_exit(AREA1 + "room66", dirs);
    if (!random(4))  dirs = ran_exit(AREA1 + "room67", dirs);
}
