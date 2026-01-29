/*
 * watchtower_top_30_19.c
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
    set_short("Abandoned watchtower top");
    set_long("Top of an abandoned watchtower, stairs down.\n");

    add_exit(ROOM + "watchtower_30_19", "down");
}
