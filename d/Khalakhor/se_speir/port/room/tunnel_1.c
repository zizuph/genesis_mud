/*
 * tunnel_1.c
 *
 * A tunnel beneath the village which contains a number of small
 * goblins for newbies to bang away at for a decent quest.
 *
 * Khail - April 20/97
 */
#pragma strict_types

#include "room.h"
#include "/d/Khalakhor/sys/defs.h"
#include <macros.h>

inherit TUNNEL_BASE;

public void
create_khalakhor_room()
{
    create_tunnel();

    extra = "A small ladder leans against the wall here, leading " +
        "upwards through a hole in the roof, through which you can " +
        "see light.\n";

    add_exit(ROOM + "tunnel_2", "north");
}

public int
do_climb(string str)
{
    NF("Climb what?\n");

    if (!str || !strlen(str))
        return 0;

    if (!parse_command(str, TP, "[up] [the] 'ladder'"))
        return 0;

    write("You climb up the ladder through the hole in the ceiling.\n");
    say(QCTNAME(TP) + " climbs up the ladder through the hole in the " +
        "ceiling.\n");
    TP->move_living("M", ROOM + "fishmonger");
    say(QCTNAME(TP) + " suddenly pops up from behind a barrel.\n");
    return 1;
}

public void
init()
{
    ::init();
    add_action(do_climb, "climb");
}
