/*
 *	/d/Gondor/anorien/nimrais/trolls/path1.c
 *
 *	Coded by Elessar, 1992
 *
 *	Modification log:
 *	Olorin:			Added herbs.
 *	 7-Feb-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"

public void
create_area_room()
{
    string *herbs;

    set_areatype(2);
    set_areadesc("hillside");
    set_grass("thick ");
    set_area("central");
    set_areaname("the White Mountains");
    set_land("Gondor");
    set_extraline("The terrain slopes more steeply here than further north " +
        "in the valley. The valley continues south, narrowing as it cuts " +
        "into the clefts of the White Mountains. It seems to be possible " +
        "to find a way up the hillside here. North the valley seems to " +
        "widen out.");
    add_exit(ANO_DIR + "nimrais/rimvalley2",   "north", 0, 2);
    add_exit(ANO_DIR + "nimrais/rimvalley3",   "south", 0, 2);
    add_exit(ANO_DIR + "nimrais/trolls/path2", "up",    0, 4);

    herbs = HERB_MASTER->query_herbs( ({ "middle earth", "hills", "moderate", }));
    set_up_herbs( ({ ONE_OF_LIST(herbs), ONE_OF_LIST(herbs), 
		     ONE_OF_LIST(herbs),}),
		  ({ }), 3);
}

