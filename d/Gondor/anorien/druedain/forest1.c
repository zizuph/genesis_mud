/*
 *	/d/Gondor/anorien/druedain/forest1.c
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
    set_areadesc("clearing");
    set_area("western");
    set_areaname("Druedain Forest");
    set_land("Anorien");
    set_grass("soft, light green");
    set_treetype("tall oaks");
    set_forest_density(8);
    set_extraline("The clearing is not big, as the oaks are growing quite "+
        "close together here, but it should be possible to continue "+
        "both north and east.");
    add_item( ({ "herbs", "flowers" }), BSN(
        "The green field is overgrown with flowers and plants here, since "+
        "the tree-crowns fail to block out the sun. The smell of the herbs and "+
        "flowers is refreshing."));
    add_item("ground",
        "The ground is overgrown with green plants and colourful flowers.\n");
    add_item("clearing", BSN(
        "The clearing is not wide, but wide enough that sunlight gets through "+
        "to the ground here, nurturing flowers and plants on the green glade."));

    add_exit(ANO_DIR + "road/wr8",      "north", test_track, 2, 1);
    add_exit(DRUEDAIN_DIR + "oldroad1", "east",  test_loc,   2, 1);

    set_up_herbs( ({ HERB_DIR + "attanar", HERB_DIR + "suranie", }),
		  ({ "ground", "field", }), 3);
}

