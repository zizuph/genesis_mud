/*
 *	/d/Gondor/anorien/druedain/forest5.c
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
    string *herbs = HERB_MASTER->query_herbs("forest");

    set_areatype(7);
    set_areadesc("overgrown path");
    set_area("northern");
    set_areaname("Druedain Forest");
    set_land("Anorien");
    set_grass("soft, green");
    set_treetype("pine");
    set_forest_density(15);
    set_extraline("You are standing on an overgrown path among some pine trees, " +
        "wondering where to go next. The path seems to enter a small glade to " +
        "the west.");
    add_item("path", BSN(
        "The path is almost disappearing beneath sprouting green plants, " +
        "as it probably is not used much at all anymore."));

    add_exit(DRUEDAIN_DIR + "forest15", "north", test_loc, 2, 1);
    add_exit(DRUEDAIN_DIR + "forest7",  "east",  test_loc, 2, 1);
    add_exit(DRUEDAIN_DIR + "forest6",  "south", test_loc, 2, 1);
    add_exit(DRUEDAIN_DIR + "forest3",  "west",  test_loc, 2, 1);

    set_up_herbs( ({ HERB_DIR + "attanar", HERB_DIR + "blueberry", 
		     HERB_DIR + "thyme", }), 
		  ({ "forest", "ground", }), 4);
}

