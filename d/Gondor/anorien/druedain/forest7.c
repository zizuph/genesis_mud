/*
 *	/d/Gondor/anorien/druedain/forest7.c
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
    set_areadesc("hidden path");
    set_area("northern");
    set_areaname("Druedain Forest");
    set_land("Anorien");
    set_grass("soft, green");
    set_treetype("oak");
    set_forest_density(18);
    set_extraline("You are standing on a hidden path among some oak trees, wondering " +
        "where to go next. The path seems to enter a small glade to the east.");

    add_exit(DRUEDAIN_DIR + "forest15", "north", test_loc,   2, 1);
    add_exit(DRUEDAIN_DIR + "forest9",  "east",  test_track, 2, 1);
    add_exit(DRUEDAIN_DIR + "forest8",  "south", test_loc,   2, 1);
    add_exit(DRUEDAIN_DIR + "forest5",  "west",  test_track, 2, 1);

    set_up_herbs( ({ ONE_OF_LIST_WITH_SEED(herbs, 701),
		     ONE_OF_LIST_WITH_SEED(herbs, 702),
		     ONE_OF_LIST_WITH_SEED(herbs, 703), }),
		  ({ "forest", "ground", }), 4);
}
