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
    return "east";
}

public void
create_road()
{
    set_short("wide dirt road");
    set_long("   You are on a wide dirt road leading east " +
        "and west through the interior of Port Macdunn. " +
        "To the south, the road is flanked by a low " +
        "stone wall. A small, grassy hill stands on " +
        "the north side of the road, however. You also " +
        "detect a faint fishy odour coming from " +
        "somewhere to the east.\n");

    add_exit(ROOM + "road_17_7", "east");
    add_exit(ROOM + "road_15_7", "west");
}
