/*
 * This is the ninth room on first road in Port Macdunn.
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
        "lies beyond the building to the north. The town is " +
        "nothing particularly amazing in size, but the large " +
        "stone buildings are well made, and the dirt roads well " +
        "maintained. To the south, you can see the numerous " +
        "piers of Port Macdunn jutting out into the waters of " +
        "Cala Fasgadh. Northeast, a small trail leads across a " +
        "wide patch of grass between buildings.\n");

    add_exit(ROOM + "road_12_8", "northeast");
    add_exit(ROOM + "road_12_9", "east");
    add_exit(ROOM + "road_10_9", "west");
    add_exit("delivery", "north");
}
