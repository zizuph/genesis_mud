/*
 *	/d/Gondor/ithilien/road/nr11.c
 *
 *	Coded by Olorin, 1993
 *
 *	Modification log:
 *	 1-Feb-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/ithilien/road/road.c";

#include "/d/Gondor/defs.h"

#define BLACK_RIDER_ROOM	"/d/Gondor/morgul/blackrider"

public int     block_ithil();

public void
create_area_room()
{
    set_areatype(8);
    set_areadesc("heathland");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_extraline("The road runs north towards Morannon, south to the "
      + "crossroads where this road meets the road from Osgiliath to "
      + "Minas Morgul. It has been made in a long lost time, but here "
      + "it has been newly repaired. East of the road, the dark "
      + "shadows of the Ephel Duath are rising, covered with sombre "
      + "trees like dark clouds. To the west lies a tumbled heathland, "
      + "grown with ling and broom and cornel. Across the heathland, a "
      + "narrow path is leading northwest.\n");
    add_mountains(1, "less than a league", 
	"The roots of the hills are rising next to the road " +
        "and are covered with sombre trees like dark clouds.");
    add_road(5);
    add_forest(5,
        "To the south, these knots become more numerous, with fir " +
        "and cedar and cypress mingling with the pine-trees.");

    add_exit(ITH_DIR + "road/nr12","north", test_exit, 3);
    add_exit(ITH_DIR + "road/nr10","south", test_exit, 3);
    add_exit(ITH_DIR + "dagorlad/path1","northwest",   block_ithil, 3);

    BLACK_RIDER_ROOM->load_me();
}

static int
query_lookout_message()
{
    /* This function returns 1 to make sure patrol.h reports to the room
     * /d/Gondor/ithilien/nforest/lookout.c that a living entered.
     * Elessar, Jan 18, 1995, to fix the problems with GD and mudlib change.
     */
    return 1;
}

public int
block_ithil()
{
    if (TP->id("_morgul_monster"))
	return 1;
    return 0;
}
