/*
 *	/d/Gondor/ithilien/road/sr6.c
 *
 *	Coded by Olorin.
 *
 *	Modification log:
 *	 3-Feb-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/ithilien/road/road.c";

#include "/d/Gondor/defs.h"

public int
cross_bridge()
{
    int     result;

    if (!(result = test_exit()))
	write("You cross the small river on the ancient stone bridge.\n");
    return result;
}

public void
create_area_room()
{
    set_areatype(8);
    set_areadesc("forest");
    set_area("southern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_extraline("The road runs south towards Harad west of the slopes of the " +
        "Ephel Duath. Just north of here, it crosses a small river on an " +
        "ancient stone bridge. West of the road a valley opens between the " +
        "green hills of Emyn Arnen.");

    add_mountains(1, "only a little more than a mile");
    add_road(-3);
    add_forest(-2);

    add_emyn_arnen("Here a small valley opens between " +
		 "two of the hills, leading into Emyn Arnen.");
    add_item(({"river", "bridge"}), BSN(
        "The small river comes running down the slopes of the Ephel Duath. " +
        "The road crosses it on an ancient stone bridge that spans the river " +
        "bed in one single arch. The river continues into the small valley " +
        "to the west."));
    add_item(({"valley"}), BSN(
        "The small valley opens between two gentle hills. It leads westward " +
        "into the land of Emyn Arnen. A small road is leading southwest " +
        "from here into the valley."));
    add_exit(ITH_DIR + "road/sr5", "north",            cross_bridge, 4);
    add_exit(ITH_DIR + "road/sr7", "south",            test_exit,    4);
    add_exit(ITH_DIR + "emyn-arnen/srd1", "southwest", test_exit,    3);
}

