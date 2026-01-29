/*
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
    return "north";
}

public void
create_road()
{
    set_short("wide dirt road");
    set_long("   The dirt road you are on turns suddenly " +
        "west and southeast here, and also branches " +
        "directly north along a slightly narrower road. " +
        "To the northwest, the stone walls of the " +
        "village's buildings is broken by a small " +
        "grassy hill. The smell of fish is rather " +
        "strong here, apparently coming from the " +
        "fishmonger's shop to the south.\n");

    add_exit(ROOM + "road_17_6", "north");
    add_exit(ROOM + "road_18_8", "southeast");
    add_exit(ROOM + "fishmonger", "south");
    add_exit(ROOM + "road_16_7", "west");
}
