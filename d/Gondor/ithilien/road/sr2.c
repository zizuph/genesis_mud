/*
 *	/d/Gondor/ithilien/road/sr2.c
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
    int    result;

    if (!(result = test_exit()))
	write("Going north, you cross the Morgulduin on the ancient stone bridge.\n");
    return result;
}

public void
create_area_room()
{
    set_areatype(8);
    set_areadesc("forest");
    set_area("central");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_extraline("The road runs south towards Harad, and north it crosses the " +
        "foul-smelling Morgulduin stream on an ancient stone bridge. Across " +
        "the bridge, you can see a ring of trees. To the east of the road, " +
        "the slopes of the Ephel Duath rise high up into the sky, to the west " +
        "the southern fringes of a green forest can be seen.");

    add_mountains(1, "only about half a mile");
    add_road(-1);
    add_tree_ring("north");
    add_forest(1, 0, ({ "forest", "wood", "woods", }) );

    add_item("bridge",BSN("The road goes over a bridge here, across the " +
        "foul-smelling stream named the Morgulduin, the River of Dark Sorcery. " +
        "Considering the smell, you do not think the name is far off."));
    add_item(({"stream","river"}),BSN(
        "The Morgulduin runs under the bridge here, dark and steaming. " +
        "It comes running west out of the dark valley of Imlad Morgul. The " +
        "reeks rising from the water are enough to make you quite nauseous, " +
        "and your stomach insists that you move on."));
    add_item(({"valley","imlad morgul"}), BSN(
        "The vale of the Morgulduin, Imlad Morgul, lies to the west, " +
        "North of the river you can see a road winding into the valley, " +
        "climbing west on a small rock shelf between a rock wall and the river. " +
        "A shimmering, ghostly light glows in the valley."));

    add_exit(ITH_DIR + "road/sr1","north", cross_bridge, 3);
    add_exit(ITH_DIR + "road/sr3","south",    test_exit, 3);
}

