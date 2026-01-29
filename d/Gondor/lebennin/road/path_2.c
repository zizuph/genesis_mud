/*
 *	/d/Gondor/lebennin/road/path2.c
 *
 *	Coded by Dunstable or Xeros (?)
 *
 *	Modification log:
 *	Updated code - 05/06/96 - By Arren
 *	28-Jan-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

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
   
    add_exit(LEB_DIR + "road/path_1",   "east", 0, 3);
    add_exit(LEB_DIR + "road/pathend", "west", 0, 3);

    add_item( ({"trees","tree"}), 
         "These evergreen pines are taller and wider than the average pine.\n");
   
    set_extraline("This path leads west and east through the ring of trees " +
	"surrounding the vast fields of Lebennin. The trees begin to close " +
	"in on the path here.");

    set_up_herbs( ({ ONE_OF_LIST_WITH_SEED(HERB_MASTER->query_herbs("forest"), 1), 
		     ONE_OF_LIST_WITH_SEED(HERB_MASTER->query_herbs("subtropical"), 1), 
		     ONE_OF_LIST_WITH_SEED(HERB_MASTER->query_herbs("lebennin"), 1), }),
		 ({ "forest", }), 5);

    add_item(({"sign","signs"}), 
	"The signs you see are tracks and what you think to be a den to the south.\n");
    add_item(({"den"}),
        "This den holds foxes.\n");
    add_item(({"path","trail","track"}), 
        "This narrow path is well-marked but looks rather unused.\n");

    reset_room();
}

public void
reset_room()
{
    ::reset_room();

    clone_npcs(Fox, NPC_DIR + "fox", 120.0 + rnd() * 120.0, LEB_DIR);
}
