/*
 * road_10_7.c
 *
 * This is part of a road in Port Macdunn.
 *
 * Khail - May 16/97
 */
#pragma strict_types

#include "room.h"

inherit ROADBASE;

public string
query_dir_to_jail()
{
    return "east";
}

public void
create_road()
{
    set_short("wide dirt road");
    set_long("   You are on a wide dirt road leading east " +
        "and west through the interior of Port Macdunn. " +
        "Low stone buildings seem to line the road " +
        "in all directions. The one to the south is " +
        "unremarkable, but the building immediately " +
        "north of you appears to be a smithy.\n");

    add_exit(ROOM + "blacksmith_forge", "north");
    add_exit(ROOM + "road_11_7", "east");
    add_exit(ROOM + "road_9_7", "west");
}
