/*
 *	/d/Gondor/rohan/farm/meadow1.c
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
    set_treetype("maple");

    set_extraline("The grass is trampled down here.");
    add_exit(FARM_DIR + "meadow2",    "south", 0, 1, 1);
    add_exit(FARM_DIR + "farm/path4", "west",  0, 1, 1);

    set_up_herbs( ({ HERB_DIR + "athelas", HERB_DIR + "basil",
		     HERB_DIR + "thyme", }),
		 ({"bushes","meadow","forest","path","here"}), 4);
}
