/* 
 *	/d/Gondor/olorin/farm/farm/path1.c
 *	It belongs to a small farm in the Ered Nimrais
 *
 *	Coded by Olorin, Nov 1992.
 *
 *	Modification log:
 *	30-Jan-1997, Olorin:	General revision.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_area_room() 
{
    set_areadesc("field");
    set_areatype(2);
    set_area("west");
    set_areaname("the White Mountains");
    set_land("Gondor");
    set_mountain("Ered Nimrais");
    set_grass("dark green ");
    set_treetype("birch");
    set_extraline("You are on a path leading north and south. To the south you "
        + "can see some small cottages through the bushes and small trees that "
        + "surround you.");
    add_exit(FARM_DIR + "entrance",   "north");
    add_exit(FARM_DIR + "farm/path2", "south");

//    set_noshow_obvious(1);
 
    set_up_herbs( ({ HERB_DIR + "dill", HERB_DIR + "suranie", }),
		  ({ "bushes", "grass", "forest", "path", }), 5);

    add_item(({"bush","bushes"}), 
        "You are surrounded by a thicket of bushes. In midst of the " +
        "bushes, a few slender birch trees are growing. The dense thicket " +
        "prevents progress in all direction but south and north, where a " +
        "small path is running through the bushes.\n");
    add_item(({"path"}), 
        "A small path is running from south to north through the bushes.\n");
    add_item(({"cottage","cottages","farm"}), 
        "Through the bushes to the south you can see a few buildings. " +
        "You can make out some cottages and stables, probably there is a " +
        "small farm at the end of the path.\n");

    reset_room();
}

public void
reset_room()
{
    if (!objectp(present("corpse", TO)))
        clone_object(OBJ_DIR + "rocorpse")->move(TO);
}
