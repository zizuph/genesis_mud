/*	
 *	/d/Gondor/olorin/farm/forest1.c 
 *	It belongs to a small farm in the Ered Nimrais
 *	Coded by Olorin, Nov 1992
 *
 *	Modification log;
 *	28-Jan-1997, Olorin:	Changed inheritance,
 *				general revision.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_area_room() 
{
    string *herbs;

    set_areadesc("group of bushes");
    set_areatype(7);
    set_area("west");
    set_areaname("the White Mountains");
    set_land("Gondor");
    set_mountain("Ered Nimrais");
    set_grass("dark green ");
    set_treetype("oak");
    set_extraline("There is a path to the west. The forest continues in all "
      + "other directions.");
    add_exit(FARM_DIR + "forest2", "north");
    add_exit(FARM_DIR + "forest2", "east");
    add_exit(FARM_DIR + "forest2", "south");
    add_exit(FARM_DIR + "farm/path2", "west");
    add_item("bushes", BSN("An apparently impenetrable thicket "
      + "made out of thick-leaved and thorny bushes. You cannot "
      + "make out anything more without a closer inspection."));

    herbs = HERB_MASTER->query_herbs( ({ "forest", "middle earth", }) );
    set_up_herbs( ({ ONE_OF_LIST_WITH_SEED(herbs, 838913),
		     ONE_OF_LIST_WITH_SEED(herbs, 321913),
		     ONE_OF_LIST_WITH_SEED(herbs, 979462), }),
		  ({ }), 5);
}
