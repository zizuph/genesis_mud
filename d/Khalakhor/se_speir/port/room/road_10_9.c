/*
 * This is the eighth room on first road in Port Macdunn.
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
    set_short("harbourfront road");
    set_long("   You are on a road leading east and west along " +
        "the southern edge of Port Macdunn, on the north " +
        "shore of the harbour, Cala Fasgadh. The town itself " +
        "lies beyond the harbour master's " +
        "building to the north. The town is nothing " +
        "particularly amazing in size, but the large stone " +
        "buildings are well made, and the dirt roads well " +
        "maintained. To the south, you can see the numerous " +
        "piers of Port Macdunn jutting out into the waters of " +
        "Cala Fasgadh. Just west of here you see an intersection " +
        "that will take you north into town or south onto those " +
        "piers.\n");

    add_exit(ROOM + "h_master", "north");
    add_exit(ROOM + "road_11_9", "east");
    add_exit(ROOM + "road_9_9", "west");
}
