/* 
 *	/d/Gondor/olorin/farm/forest3.c
 *	It belongs to a small farm in the Ered Nimrais
 *
 *	Olorin, Nov 1992
 *
 *	Modification log:
 *	30-Jan-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_area_room() 
{
    string *herbs;

    set_areadesc("place somewhere");
    set_areatype(7);
    set_area("west");
    set_areaname("the White Mountains");
    set_land("Gondor");
    set_mountain("Ered Nimrais");
    set_grass("dark green");
    set_treetype("pine");
    add_exit(FARM_DIR + "forest3",    "north");
    add_exit(FARM_DIR + "farm/path2", "east");
    add_exit(FARM_DIR + "forest3",    "south");
    add_exit(FARM_DIR + "forest3",    "west");

    herbs = HERB_MASTER->query_herbs( ({ "forest", "middle earth", }) );
    set_up_herbs( ({ ONE_OF_LIST_WITH_SEED(herbs, 299409),
		     ONE_OF_LIST_WITH_SEED(herbs, 699296),
		     ONE_OF_LIST_WITH_SEED(herbs, 124244), }),
		  ({ }), 5);
}
