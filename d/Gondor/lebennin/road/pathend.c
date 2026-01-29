/*
 *	/d/Gondor/lebennin/road/path1.c
 *
 *	Coded by Dunstable or Xeros (?)
 *
 *	Modification log:
 *	Updated code - 05/06/96 - By Arren
 *	 3-Feb-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/lib/herb_list.h"

#define MAX_FOX 2

static object *Fox = allocate(MAX_FOX);

public void
create_area_room()
{
    set_area("central");
    set_areaname("Lebennin");
    set_land("Gondor");
    set_areatype(7);
    set_areadesc("path");
    set_grass("green");
    set_treetype("oak");
   
    add_exit(LEB_DIR + "road/path_2", "east", 0, 3);

    add_item( ({ "tree", "trees", }),
        "This tree is an oak just like the others around.\n");
   
    set_extraline("This path ends here in a dense patch of trees.");

    set_up_herbs( ({ ONE_OF_LIST_WITH_SEED(HERB_MASTER->query_herbs("forest"), 1), 
		     ONE_OF_LIST_WITH_SEED(HERB_MASTER->query_herbs("subtropical"), 1), 
		     ONE_OF_LIST_WITH_SEED(HERB_MASTER->query_herbs("lebennin"), 1), 
		     HERB_DIR + "red_pepper", }),
		 ({ "forest", "path", "ground", }), 5);

    add_item( ({ "patch", }), BSN(
         "The patch of trees is so dense you see no light coming from the other "+
         "side even in daylight."));
    add_item( ({ "path", "trail", "track", }),
         "This narrow path is well-marked but looks rather unused.\n");

}

public void
reset_room()
{
    ::reset_room();

    clone_npcs(Fox, NPC_DIR + "fox", 120.0 + rnd() * 120.0, LEB_DIR);
}

