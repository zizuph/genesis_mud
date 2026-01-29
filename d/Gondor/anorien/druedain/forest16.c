/*
 *	/d/Gondor/anorien/druedain/forest16.c
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
    set_areadesc("thicket");
    set_area("northern");
    set_areaname("Druedain Forest");
    set_land("Anorien");
    set_grass("soft, green");
    set_treetype("large pine");
    set_forest_density(50);
    set_extraline("You are standing in a thicket of large trees and underbrush, " +
        "wondering where to go next.");

    add_exit(DRUEDAIN_DIR + "forest16", "north", test_loc, 2, 1);
    add_exit(DRUEDAIN_DIR + "forest12", "east",  test_loc, 2, 1);
    add_exit(DRUEDAIN_DIR + "forest9",  "south", test_loc, 2, 1);
    add_exit(DRUEDAIN_DIR + "forest15", "west",  test_loc, 2, 1);

    set_up_herbs( ({ ONE_OF_LIST_WITH_SEED(herbs, 1601),
		     ONE_OF_LIST_WITH_SEED(herbs, 1602),
		     ONE_OF_LIST_WITH_SEED(herbs, 1603), }),
		  ({ "forest", "ground", }), 8);
}
