/*
 *	/d/Gondor/anorien/druedain/forest3.c
 *
 *	Coded by Elessar.
 *
 *	Modification log:
 *	 5-Feb-1997, Olorin:	Changed inheritance,
 *				general revision.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"

public void
create_area_room()
{
    set_areatype(7);
    set_areadesc("glade");
    set_area("northern");
    set_areaname("Druedain Forest");
    set_land("Anorien");
    set_grass("soft, green");
    set_treetype("tall grey");
    set_forest_density(12);
    set_extraline("You are standing among several tall, grey trees, wondering "+
        "where to go next. It seems to be impossible to go north, but in the "+
        "other directions the forest is less dense, and might be passable.");
    add_exit(DRUEDAIN_DIR + "forest5",  "east",  test_loc, 2, 1);
    add_exit(DRUEDAIN_DIR + "forest4",  "south", test_loc, 2, 1);
    add_exit(DRUEDAIN_DIR + "oldroad3", "west",  test_loc, 2, 1);

    set_up_herbs( ({ HERB_DIR + "suranie", HERB_DIR + "athelas",
		     HERB_DIR + "tarragon", }),
		  ({ "forest", "ground", }), 4);
}
