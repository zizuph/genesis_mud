/*
 * tunnel_8.c
 *
 * A tunnel beneath the village which contains a number of small
 * goblins for newbies to bang away at for a decent quest.
 *
 * Khail - April 20/97
 */
#pragma strict_types

#include "room.h"

inherit TUNNEL_BASE;

public void
create_khalakhor_room()
{
    goblin_num = 3;

    create_tunnel();

    add_exit(ROOM + "tunnel_5", "east");
    add_exit(ROOM + "tunnel_9", "southeast");

    set_alarm(1.0, 0.0, reset_room);
}
