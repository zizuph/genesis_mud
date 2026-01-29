/*
 *	/d/Gondor/ithilien/nforest/slope.c
 *
 *	Coded 1993 by Olorin.
 *
 *	Modification log:
 *	30-Jan-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"

static object *Rabbit = allocate(2 + random(3));

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
        "basin. The slope itself is covered with brown fern, that " +
        "grows thicker further up. Beyond it, a thicket of dark-leaved " +
        "bay trees is climbing up a steep bank that is crowned with " +
        "old cedars. Sweet odours from herbs and flowers are in the " +
        "air everywhere.");
    add_item( ({"mountains","mountain-range","mountain","ephel duath"}),
	"From here the mountains are hidden by trees and the stony " +
        "ridge to the east.\n");
    add_item (({ "bank", "bay trees", "cedar", "groves", "thickets", 
	"thicket", "grove", }), BSN("Dark-leaved bay trees form a " +
        "thicket north and east of the slope. To the east, a steep " +
        "bank rises, crowned with old cedars. Only to the northeast " +
        "might one be able to continue further up the slope, into " +
        "an even thicker fern bed."));
    add_item( ({ "stream", }),
        "The small stream enters the basin south of here.\n");
    add_item( ({ "flower", "flowers", "herbs", "forest", "wood", 
        "woods", "fern", "fern bed", }), BSN(
        "The fern forms a deep brown bed here. It grows high enough " +
        "to hide someone lying down from casual glances. Among the " +
        "ferns, herbs and flowers are growing. You can recognize " +
        "mints and lilies by the smell, and parsleys are sprouting " +
        "under the trees."));
    add_item( ({ "lake", "basin", "pool", "water", }), BSN(
        "The small lake lies in the broken ruins of an ancient stone " +
        "basin. A small stream is feeding it, and at the far end the " +
        "water spills out again over a stony lip."));

    set_up_herbs( ({ HERB_DIR + "garlic",  HERB_DIR + "dill", 
		     HERB_DIR + "fennel",  HERB_DIR + "basil", 
		     HERB_DIR + "oregano", HERB_DIR + "laurel", 
		     HERB_DIR + "suranie", HERB_DIR + "foxglove", }),
		  ({ "forest", "ground", "field", "flowers", }), 3);

    add_exit(ITH_DIR + "nforest/fernbed",  "northeast", fernbed, 1);
    add_exit(ITH_DIR + "nforest/sstream3", "south",           0, 1);
    add_exit(ITH_DIR + "nforest/lake",     "west",            0, 1);
    add_exit(ITH_DIR + "nforest/slope2",   "northwest",       0, 1);

    reset_room();
}

public void
reset_room()
{
    set_searched(- random(3));

    clone_npcs(Rabbit, NPC_DIR + "rabbit", 30.0 + rnd() * 60.0, 
	       ITH_DIR + "nforest/");
}

