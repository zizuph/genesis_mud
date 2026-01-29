/*
 * tunnel_6.c
 *
 * A tunnel beneath the village which contains a number of small
 * goblins for newbies to bang away at for a decent quest.
 *
 * Khail - April 20/97
 */
#pragma strict_types

#include "room.h"
#include <stdproperties.h>

inherit TUNNEL_BASE;

public void
create_khalakhor_room()
{
    extra = "This room is a dead end, and between the torch " +
        "sputtering on a wall and the filthy hay paddocks strewn " +
        "around the floor, appears to be a living chamber.\n";
    goblin_num = 4;

    create_tunnel();

    add_item(({"torch"}),
        "The torch is a simple stick with one end wrapped in an " +
        "oil soaked rag. It's nothing fancy, but works well enough " +
        "to shed a bit of light.\n");
    add_item(({"hay", "paddocks", "hay paddocks"}),
        "They aren't very big, or thick, but the hay looks like " +
        "it's been lying there for a year or two, and is so filthy " +
        "it's barely recognizable as hay.\n");

    LIGHT;

    add_exit(ROOM + "tunnel_5", "west");

    set_alarm(1.0, 0.0, reset_room);
}
