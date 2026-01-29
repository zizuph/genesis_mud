/*
 *	/d/Gondor/rohan/farm/farm/path4.c
 *
 *	It belongs to a small farm in the Ered Nimrais.
 *
 *	Coded November 1992 by Olorin.
 *
 *	Modification log:
 *	28-Jan-1997, Olorin:	General revision.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_area_room() 
{
    set_areadesc("path");
    set_areatype(7);
    set_area("west");
    set_areaname("the White Mountains");
    set_land("Gondor");
    set_mountain("Ered Nimrais");
    set_grass("dark green");
    set_treetype("maple");
    set_extraline("The path is leading northwest to south. To the east " +
        "is a meadow.");

    add_exit(FARM_DIR + "meadow1", "east",0,0,1);
    add_exit(FARM_DIR + "farm/path3", "south");
    add_exit(FARM_DIR + "farm/yard1", "northwest");

    set_up_herbs( ({ HERB_DIR + "garlic", 
	     ONE_OF_LIST_WITH_SEED(HERB_MASTER->query_herbs("forest"), 42),
	     ONE_OF_LIST_WITH_SEED(HERB_MASTER->query_herbs("middle earth"), 42), }), 
		 ({ "bushes", "meadow", "forest", "path", }), 5);
}
