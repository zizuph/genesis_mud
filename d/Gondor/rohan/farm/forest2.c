/* 
 *	/d/Gondor/olorin/farm/forest2.c
 *	It belongs to a small farm in the Ered Nimrais
 *	Olorin, Nov 1992
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
    set_treetype("beech");
    add_exit(FARM_DIR + "forest1", "west");
    add_exit(FARM_DIR + "forest2", "north");
    add_exit(FARM_DIR + "forest2", "east");
    add_exit(FARM_DIR + "forest2", "south");
//    set_noshow_obvious(1);

    herbs = HERB_MASTER->query_herbs( ({ "forest", "middle earth", }) );
    set_up_herbs( ({ ONE_OF_LIST_WITH_SEED(herbs, 501534),
		     ONE_OF_LIST_WITH_SEED(herbs, 112173),
		     ONE_OF_LIST_WITH_SEED(herbs, 279731), }),
		  ({ }), 5);
}
