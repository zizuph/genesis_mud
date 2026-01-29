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
    set_short("narrow dirt road");
    set_long("   You are on a narrow dirt road leading " +
        "south and west at the northeastern " +
        "corner of the village. At the inner edge of " +
        "the turn stands the wall of a stone building " +
        "of some sort, but immediately east of here " +
        "stands the open entrance into the village " +
        "jail. To the north, a low earthen embankment " +
        "marks the edge of town.\n");

    add_item(({"jail"}),
        "The jail looks much like all the other buildings " +
        "in Port Macdunn, with the possible exception " +
        "of sturdier construction. It also serves as the " +
        "garrison for the village militia.\n");

    add_exit(ROOM + "jail", "east");
    add_exit(ROOM + "road_17_3", "south");
    add_exit(ROOM + "road_16_2", "west");
}
