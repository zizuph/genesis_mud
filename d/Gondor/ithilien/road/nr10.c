/*
 *	/d/Gondor/ithilien/road/nr10.c
 *
 *	Coded by Olorin, 1993
 *
 *	Modification log:
 *	 1-Feb-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/ithilien/road/road.c";

#include "/d/Gondor/defs.h"

public void
create_area_room()
{
    set_areatype(8);
    set_areadesc("forest");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_extraline("The road runs north towards Morannon, south to the crossroads " +
        "where this road meets the road from Osgiliath to Minas Morgul. It has been " +
        "made in a long lost time. The handiwork of the Men of old can " +
        "still be seen in its straight sure flight and level course. To " +
        "the north, it has been newly repaired. But looking south, one " +
        "can see heather and trees overhanging the banks. The mountains " +
        "are receding eastwards here in a long curve. To the west, gentle " +
        "slopes running down towards the valley of the Anduin are covered " +
        "with small woods of resinous trees, fir and cedar and cypress and " +
        "other kinds, with wide glades between them. Further north, the " +
        "forest grows thinner, turning into a heathland.\n");
    add_forest(2);
    add_mountains(1, "several leagues");
    add_road(4);
    add_exit(ITH_DIR + "road/nr11", "north", test_exit, 3);
    add_exit(ITH_DIR + "road/nr9",  "south", test_exit, 3);
}

static int
query_lookout_message()
{
    /* patrol.h checks this, to see if it should report that a living
     * entered this room to /d/Gondor/ithilien/nforest/lookout.c
     * Since we return 1, it will report.
     */
    return 1;
}

