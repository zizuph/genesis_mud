/*
 *	/d/Gondor/ithilien/road/sr3.c
 *
 *	Coded by Olorin.
 *
 *	Modification log:
 *	 3-Feb-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/ithilien/road/road.c";

#include "/d/Gondor/defs.h"

public void
create_area_room()
{
    set_areatype(8);
    set_areadesc("forest");
    set_area("central");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_extraline("The road runs south towards Harad west of the slopes " +
        "of the Ephel Duath. In some distance to the north, you can make " +
        "a stone bridge crossing a river, and beyond the bridge, a ring of trees. " +
        "To the west of the road, there are the southern fringes of a great forest.");

    add_mountains(1, "only about a mile");
    add_road(-2);
    add_tree_ring("north");
    add_forest(-1, 0, ({"forest","fringe","fringes"}) );

    add_item(({"bridge","river","stream","morgulduin"}), BSN(
        "Further north, the road goes over a bridge across the Morgulduin. " +
        "The river comes running out of the dark valley of Imlad Morgul. Even " +
        "from this distance you cannot fail to smell the reeks rising from the foul " +
        "water of the stream."));
    add_item(({"valley","imlad morgul"}), BSN(
        "The vale of the Morgulduin, Imlad Morgul, lies to the northwest, " +
        "North of the river you can see a road winding into the valley, " +
        "climbing west on a small rock shelf between a rock wall and the " +
        "river. A shimmering, ghostly light glows in the valley."));

    add_exit(ITH_DIR + "road/sr2","north",        test_exit, 4);
    add_exit(ITH_DIR + "road/sr4","south",        test_exit, 4);
    add_exit(ITH_DIR + "sforest/thicket1","west", test_exit, 2);
}

