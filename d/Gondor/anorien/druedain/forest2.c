/*
 *	/d/Gondor/anorien/druedain/forest2.c
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
    set_areadesc("field");
    set_area("northern");
    set_areaname("Druedain Forest");
    set_land("Anorien");
    set_grass("soft, green");
    set_treetype("tall grey");
    set_forest_density(11);
    set_extraline("You are standing among several tall, grey trees, wondering "+
        "where to go next. It seems to be impossible to go east, but the "+
        "other directions the forest is less dense, and might be passable.");
    add_exit(ANO_DIR + "road/wr6",      "north", test_loc, 2, 1);
    add_exit(DRUEDAIN_DIR + "oldroad2", "south", test_loc, 2, 1);
    add_exit(DRUEDAIN_DIR + "oldroad1", "west",  test_loc, 2, 1);
    add_item( ({ "field", "glade", }), BSN(
	"The glade is sprinkled with flowers and herbs, some stretching "+
        "tall to grasp the rays of sunlight that gets through the "+
        "branches above."));
    add_item( ({ "flowers", "herbs", }), BSN(
        "Here and there you spot red flowers, and there are patches "+
        "of green growths with berries in areas where the sun is not as "+
        "often seen. It all seems like a natural herb-garden."));
    add_item("ground", BSN(
        "Green growths and flowers cover the ground in this glade, obviously "+
        "because the sun comes more easily through here than in the denser parts "+
        "of the forest."));

    set_up_herbs( ({ HERB_DIR + "lothore", HERB_DIR + "suranie", 
		     HERB_DIR + "tuo", }),
		  ({ "ground", "glade", "field", }), 3);
}
