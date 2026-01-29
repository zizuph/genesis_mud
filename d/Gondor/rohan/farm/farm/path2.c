/*
 *	/d/Gondor/olorin/farm/farm/path2.c
 *	It belongs to a small farm in the Ered Nimrais
 *	Olorin, Nov 1992
 *	Modification log:
 *      July 1995, Olorin:	Inherited herbsearch.c.
 *	29-Jan-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

static object *Dunlist = allocate(2);

public void
reset_room()
{
    ::reset_room();

    clone_npcs(Dunlist, NPC_DIR + "farm/dunlending", 10.0);
}

public void
create_area_room() 
{
    set_areadesc("path");
    set_areatype(7);
    set_area("west");
    set_areaname("the White Mountains");
    set_land("Gondor");
    set_grass("dark green");
    set_treetype("maple");
    set_extraline("The path is leading north to south. To the south you "
      + "can see a small cottage and two stables.");

    add_item(({"clearing", "cottage", "farm house", "house", }), 
        "Between the trees to the south, in a small clearing stands "
      + "a cottage. You cannot make out details from here, but you "
      + "see that the walls are made from hewn grey rocks, while the roof "
      + "is covered by wooden shingles.");
    add_item(({"stable", "stables", }), 
        "Next to the cottage in the clearing to the south are two "
      + "stables built from wooden boards.");

    add_exit(FARM_DIR + "farm/path1", "north");
    add_exit(FARM_DIR + "forest1", "east",0,0,1);
    add_exit(FARM_DIR + "farm/yard1", "south");
    add_exit(FARM_DIR + "forest3", "west",0,0,1);

    set_up_herbs( ({ HERB_DIR + "rosemary", HERB_DIR + "fennel", }),
                  ({"bushes","grass","forest","path","here"}), 2);

    reset_room();
}

