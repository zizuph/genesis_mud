/*
 *	/d/Gondor/ithilien/nforest/slope2.c
 *
 *	Coded 1993 by Olorin.
 *
 *	Modification log:
 *	30-Jan-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"

public int
fernbed()
{
    write("You crawl deeper into the thick fernbed.\n");
    return 0;
}

public void
create_area_room()
{
    set_areatype(7);
    set_areadesc("fern-covered slope");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_treetype("bay and cedar");
    set_extraline("The slope is overlooking a small lake in a shallow " +
        "dell. The lake lies in the broken ruins of an ancient stone " +
        "basin. The slope itself is covered with brown fern. Beyond " +
        "it, a thicket of dark-leaved bay trees is climbing up a steep " +
        "bank that is crowned with old cedars. Sweet odours from herbs " +
        "and flowers are in the air everywhere.");
    add_item(({"mountains","mountain-range","mountain","ephel duath"}),
        "From here the mountains are hidden by trees and the stony " +
        "ridge to the east.\n");
    add_item(({"bank","bay trees","thickets","thicket","slope"}), BSN(
        "Dark-leaved bay trees form a thicket north of the slope. The " +
        "slope continues southeast, where it meets a steep bank " +
        "crowned with old cedars."));
    add_item( ({ "stream", }), 
        "The small stream enters the basin southeast of here.\n");
    add_item( ({ "flower", "flowers", "herbs", "forest", "wood", "woods", 
        "fern", "fern bed", }), BSN(
        "The fern forms a deep brown bed here. It grows high enough " +
        "to hide someone lying down from casual glances. Among the " +
        "ferns, herbs and flowers are growing. You can recognize " +
        "mints and myrtles by the smell, and parsleys are sprouting " +
        "under the trees."));
    add_item( ({ "lake", "basin", "pool", "water", }), BSN(
        "The small lake south of here lies in the broken ruins of an " +
        "ancient stone basin. A small stream is feeding it, and at " +
        "the far end the water spills out again over a stony lip."));

    set_up_herbs( ({ HERB_DIR + "clove", HERB_DIR + "fennel", 
		     HERB_DIR + "mint",  HERB_DIR + "laurel", 
		     HERB_DIR + "lothore", }), 
		  ({ "forest", "ground", "field", "flowers", }), 3);
    add_exit(ITH_DIR + "nforest/slope",  "southeast", 0, 1);
    add_exit(ITH_DIR + "nforest/lake",   "south",     0, 1);
    add_exit(ITH_DIR + "nforest/slope3", "southwest", 0, 1);
}

