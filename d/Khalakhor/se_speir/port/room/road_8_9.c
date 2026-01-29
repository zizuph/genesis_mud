/*
 * This is the sixth room on first road in Port Macdunn.
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
    set_long("   You are on a road leading east along " +
        "the southern edge of Port Macdunn, on the north " +
        "shore of the harbour, Cala Fasgadh. The town itself " +
        "lies to the north, beyond the wall of the squat stone " +
        "building. It's nothing " +
        "particularly amazing in size, but the large stone " +
        "buildings are well made, and the dirt roads well " +
        "maintained. To the south, you can see the numerous " +
        "piers of Port Macdunn jutting out into the waters of " +
        "Cala Fasgadh, you can see an intersection just east of " +
        "here that leads down to them and further into town.\n");

    add_exit(ROOM + "road_9_9", "east");
    add_exit(ROOM + "road_7_9", "west");
}
