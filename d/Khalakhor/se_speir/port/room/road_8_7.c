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
        "The road forms a T-intersection here, with a " +
        "stretch leading away northwards. To the northwest, " +
        "the road is bordered with the high walls which " +
        "surround the courtyard of a large compound. " +
        "The south side of the road is enclosed by the walls " +
        "of buildings as far as you can see, but there's a " +
        "wide spread of grass beside the low stone building " +
        "on the north side of the road a stone's throw " +
        "to the east.\n");

    add_exit(ROOM + "road_8_6", "north");
    add_exit(ROOM + "road_9_7", "east");
    add_exit(ROOM + "road_7_7", "west");
}
