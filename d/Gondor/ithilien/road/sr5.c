/*
 *	/d/Gondor/ithilien/road/sr5.c
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
        "Ephel Duath. Just south of here, it crosses a small river on an " +
        "ancient stone bridge. West of the road the green hills of Emyn " +
        "Arnen are rising, covered by small forests.");

    add_mountains(1, "only about a mile");
    add_road(-3);
    add_forest(-2);

    add_emyn_arnen();
    add_item(({"river", "bridge"}), BSN(
        "The small river comes running down the slopes of the Ephel Duath. " +
        "The road crosses it on an ancient stone bridge that spans the river " +
        "bed in one single arch."));

    add_exit(ITH_DIR + "road/sr4", "north", test_exit,    3);
    add_exit(ITH_DIR + "road/sr6", "south", cross_bridge, 3);
}
