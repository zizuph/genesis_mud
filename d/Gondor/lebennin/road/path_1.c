/*
 *	/d/Gondor/lebennin/road/path1.c
 *
 *	Coded by Dunstable or Xeros (?)
 *
 *	Modification log:
 *	28-Jan-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_area_room()
{
    set_area("central");
    set_areaname("Lebennin");
    set_land("Gondor");
    set_areatype(3);
    set_areadesc("path");
    set_grass("green");
   
    add_exit(LEB_DIR + "road/path_2", "west", 0, 3);
    add_exit(LEB_DIR + "road/nr13",  "east", 0, 3);

    add_item( ({"trees","tree"}), 
         "These evergreen pines are taller and wider than the average pine.\n");
   
    set_extraline("This path leads west and east through the ring of trees" +
	" surrounding the vast fields of Lebennin.  The trees are so dense it" +
	" is difficult to see much around you.");

    set_up_herbs( ({ ONE_OF_LIST_WITH_SEED(HERB_MASTER->query_herbs("forest"), 1), 
		     ONE_OF_LIST_WITH_SEED(HERB_MASTER->query_herbs("subtropical"), 1), 
		     ONE_OF_LIST_WITH_SEED(HERB_MASTER->query_herbs("lebennin"), 1), }),
		 ({ "forest", }), 5);
}
