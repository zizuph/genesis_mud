/*
 * /d/Gondor/lebennin/road/wqfield4.c
 *
 *
 * Revision history:
 * Updated code - 05/06/96 - By ?
 * Changed inheritance, general revision - 6-Feb-1997, Olorin.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define MAX_GHOP 5

static object *GHop = allocate(MAX_GHOP);

public void
create_area_room()
{
    string *herbs;

    set_area("northeast");
    set_areaname("Lebennin");
    set_land("Gondor");
    set_areatype(2);
    set_areadesc("grassland");
    set_grass("tall");
   
    add_exit(LEB_DIR + "road/wqroad4","east", 0, 2);
   
    set_extraline("You are entirely surrounded by a wide expanse of rolling grassland. " +
   "To the north, the snowcovered peaks of the White Mountains rise out of " +
   "the plains of Lebennin. A narrow road, overgrown with grass, runs " +
   "towards those peaks east of here.");
    add_item(({"peaks","peak","white mountains","ered nimrais","mountains","mountain"}),    
      BSN("Most of the peaks of the Ered Nimrais are visible from here, "+
         "drawing closer like giants marching out of the northwest heading to Mordor."));
    add_item("grass","The grass is tall and dark green, with long thick blades.\n");
    add_item(({"road","path"}), BSN(
         "More of a path than a road, it is overgrown with grass. "+
         "It winds its way towards the mountains through these grasslands."));
    add_item("ground","The ground here is fairly dry but firm.\n");

    herbs = HERB_MASTER->query_herbs("meadow");
    set_up_herbs( ({ ONE_OF_LIST_WITH_SEED(herbs, 5117),
		     ONE_OF_LIST_WITH_SEED(herbs, 5118),
		     ONE_OF_LIST_WITH_SEED(herbs, 5119), }),
		 ({"grassland","bush","plain","field","ground","grass"}), 5);
    reset_room();
}

public void
reset_room()
{
   ::reset_room();

   clone_npcs(GHop, NPC_DIR + "grasshopper", 180.0, LEB_DIR + "road/");
}

