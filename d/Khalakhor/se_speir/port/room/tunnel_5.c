/*
 * tunnel_5.c
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

    add_exit(ROOM + "tunnel_7", "north");
    add_exit(ROOM + "tunnel_6", "east");
    add_exit(ROOM + "tunnel_4", "southeast");
    add_exit(ROOM + "tunnel_8", "west");

    set_alarm(1.0, 0.0, reset_room);
}
