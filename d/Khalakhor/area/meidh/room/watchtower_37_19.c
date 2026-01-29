/*
 * watchtower_30_19.c
 *
 * This is an abandoned watchtower in Meidh.
 *
 * Khail - March 2002
 */
#pragma strict_types

#include "room.h"

inherit "/d/Khalakhor/std/room";

public void
create_khalakhor_room()
{
    set_short("Abandoned watchtower");
    set_long("Abandoned watchtower, exit west, stairs up.\n");

    add_exit(ROOM + "road_37_20", "north");
    add_exit(ROOM + "watchtower_top_37_19", "up");
}
