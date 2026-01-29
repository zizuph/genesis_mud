/*
 *	/d/Gondor/rohan/farm/meadow2.c
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
    set_areadesc("meadow");
    set_areatype(3);
    set_area("west");
    set_areaname("the White Mountains");
    set_land("Gondor");
    set_mountain("Ered Nimrais");
    set_grass("dark green");
    set_treetype("birch");
    set_extraline("The grass is trampled down here. Fallen birch leaves " +
        "lay scattered on the ground");
    add_item(({"leaves", "birch leaves"}),
        "They are large, tear-shaped leaves with serrated edges. The " +
        "leaves are dried and lay scattered around on the ground.\n");

    add_exit(FARM_DIR + "meadow1",    "north", 0, 1, 1);
    add_exit(FARM_DIR + "farm/path3", "west", 0, 1, 1);

    set_up_herbs( ({ HERB_DIR + "garlic", HERB_DIR + "astaldo",
		     ONE_OF_LIST_WITH_SEED(HERB_MASTER->query_herbs("meadow"), 4711), }),
		 ({"bushes", "meadow", "forest", "path", }), 5);
}
