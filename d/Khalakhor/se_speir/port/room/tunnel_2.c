/*
 * tunnel_2.c
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
    create_tunnel();

    add_exit(ROOM + "tunnel_12", "north");
    add_exit(ROOM + "tunnel_3", "northeast");
    add_exit(ROOM + "tunnel_1", "south");
}
