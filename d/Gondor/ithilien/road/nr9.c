/*
 *	/d/Gondor/ithilien/road/nr9.c
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
        "still be seen in its straight sure flight and level course. " +
        "But the road is overgrown, and heather and trees overhang " +
        "the banks. The mountains are receding eastwards here in a long " +
        "curve. To the west, gentle slopes running down towards the valley of the " + 
        "Anduin are covered with small woods of resinous trees, fir and cedar and " +
        "cypress and other kinds, with wide glades between them.\n");
    add_forest(4);
    add_mountains(1, "several miles");
    add_road(3);
    add_exit(ITH_DIR + "road/nr10", "north", test_exit, 3);
    add_exit(ITH_DIR + "road/nr8",  "south", test_exit, 3);
}

static int
query_lookout_message()
{
  /* We return 1 here, so that patrol.h knows to report to
   * /d/Gondor/ithilien/nforest/lookout.c that a living entered
   * this room.
   * Elessar, Jan 18. 1995. Fixed after the GD and mudlib change.
   */
    return 1;
}

