/*
 *	/d/Gondor/anorien/druedain/forest9.c
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
    set_areadesc("glade");
    set_area("northern");
    set_areaname("Druedain Forest");
    set_land("Anorien");
    set_grass("soft, green");
    set_treetype("oak");
    set_forest_density(10);
    set_extraline("You are standing in a small glade among some oak trees, " +
        "wondering where to go next.\n");

    add_exit(DRUEDAIN_DIR + "forest16", "north", test_loc,   2, 1);
    add_exit(COMMON_DIR + "quest/enchant_seed/garden", "east", 0, 2, 1);
    add_exit(DRUEDAIN_DIR + "forest10", "south", test_loc,   2, 1);
    add_exit(DRUEDAIN_DIR + "forest7",  "west",  test_track, 2, 1);

    set_up_herbs( ({ ONE_OF_LIST_WITH_SEED(herbs, 901),
		     ONE_OF_LIST_WITH_SEED(herbs, 902),
		     ONE_OF_LIST_WITH_SEED(herbs, 903), }),
		  ({ "forest", "ground", }), 4);
}
