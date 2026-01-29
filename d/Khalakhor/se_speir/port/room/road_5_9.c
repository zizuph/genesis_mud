/*
 * This is the third room on first road in Port Macdunn.
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
        "rises to the north, behind the building creating a " +
        "stone wall on north side of the road. It's nothing " +
        "particularly amazing in size, but the large stone " +
        "buildings are well made, and the dirt roads well " +
        "maintained. To the southeast, you can see the numerous " +
        "piers of Port Macdunn jutting out into the waters of " +
        "Cala Fasgadh.\n");

    add_exit(ROOM + "road_6_9", "east");
    add_exit(ROOM + "road_4_9", "west");
}
