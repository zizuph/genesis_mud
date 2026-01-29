/*
 * watchtower_21_19.c
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
    set_long("Abandoned watchtower, exit north, stairs up.\n");

    add_exit(ROOM + "road_21_20", "north");
    add_exit(ROOM + "watchtower_top_21_19", "up");
}
