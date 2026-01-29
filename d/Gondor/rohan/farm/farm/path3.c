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

static object  Captain;
static object *Dunlist = allocate(3);
	
public void
create_area_room() 
{
    set_areadesc("path");
    set_areatype(7);
    set_area("west");
    set_areaname("the White Mountains");
    set_land("Gondor");
    set_mountain("Ered Nimrais");
    set_grass("dark green ");
    set_treetype("dark and threatening");
    set_extraline("The path is leading north. To the east is a "
      + "meadow. On all other sides are dark trees and thorny bushes. "
      + "You feel threatened here.");

    add_exit(FARM_DIR + "farm/path4", "north");
    add_exit(FARM_DIR + "meadow2", "east",0,0,1);
    add_exit("/d/Gondor/rohan/farm/farm/camp/rooms/p1", "southeast");

    set_up_herbs( ({ HERB_DIR + "suranie", HERB_DIR + "tuo", 
	  ONE_OF_LIST_WITH_SEED(HERB_MASTER->query_herbs("forest"), 137), }),
		 ({ "bushes", "meadow", "forest", "path", }), 5);

    reset_room();
}

public void
team_them()
{
    int     ic = -1;

    if (!objectp(Captain))
	return;

    while (++ic < sizeof(Dunlist))
	if (objectp(Dunlist[ic]))
	    Captain->team_join(Dunlist[ic]);

    Captain->command("shout Follow orders, you apes, or else!");
    Captain->set_random_move(20);
}

public void
reset_room() 
{
    ::reset_room();

    Captain = clone_npc(Captain, NPC_DIR + "farm/capdunl");
    clone_npcs(Dunlist, NPC_DIR + "farm/dunlending", 1.0);

    set_alarm(5.0, 0.0, team_them);
}


int
block_room()
{
    if (this_player()->query_wiz_level()) 
    {
        write("\n\nYou enter an area that is not open to mortals.\n\n\n");
        return 0;
    }

    write("A large tree has fallen overthepath, blocking further travel.\n");
    return 1;
}
