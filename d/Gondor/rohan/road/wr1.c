/*
 *	/d/Gondor/rohan/road/wr1.c
 *
 *	Coded by Gus (?), 1992
 *
 *	Modification log:
 *	 4-Feb-1997, Olorin:	Changed inheritance,
 *				general revision.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"

public int
bridge_msg()
{
    write("You cross the river Snowbourn on a stone bridge.\n");
    return 0;
}

public void
create_area_room()
{
    set_areatype(8);
    set_areadesc("green field");
    set_area("southern");
    set_areaname("Westfold");
    set_land("Rohan");
    set_extraline("The road continues east, crossing the river Snowbourn on an " + 
        "ancient stone bridge. Beyond the bridge, on the other bank of the " +
        "stream, are the crossroads north of the town Edoras. Northwest and " +
        "north the grassy plains of the Westfold stretch out.");
    add_exit(ROH_DIR + "plains/h07",     "north",         0, 5);
    add_exit(ROH_DIR + "road/crossroad", "east", bridge_msg, 3);
    add_exit(ROH_DIR + "road/wr2",       "northwest",     0, 3);
    add_item( ({ "bridge", "stone bridge", }), BSN("To the east, the road " +
        "crosses the river Snowbourn on an ancient stone bridge."));
    add_item( ({ "river", "snowbourn", "river snowbourn", }), BSN(
        "The river is a little east of here, rushing out of the valley to " +
        "the south with foam-topped waves, but gradually slowing down as " +
        "it enters the plains."));
}

