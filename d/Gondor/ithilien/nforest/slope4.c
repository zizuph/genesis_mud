/*
 *      /d/Gondor/ithilien/nforest/slope4.c
 *
 *      Olorin, 1993
 *
 *      Modification log:
 *      26-Jan-1997, Olorin: Changed inheritance to area_room.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";


#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

static object *Rabbit = allocate(2 + random(3));

public void
create_area_room()
{
    set_areatype(7);
    set_areadesc("fern-covered slope");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_treetype("bay and cedar");
    set_extraline("The slope is overlooking a small lake in a shallow dell. The lake lies " +
        "in the broken ruins of an ancient stone basin. The slope itself is covered with " +
        "brown fern. Beyond it, a thicket of dark-leaved bay trees blocks your progress. " +
        "Sweet odours from herbs and flowers are in the air everywhere.");

    add_exit(ITH_DIR + "nforest/slope3",  "northeast", 0, 1);
    add_exit(ITH_DIR + "nforest/bank1",   "east",      0, 1);
    add_exit(ITH_DIR + "nforest/outfall", "southeast", 0, 1);

    add_item(({"mountains","mountain-range","mountain","ephel duath"}), 
        "From here the mountains are hidden by trees and the stony ridge to the east.\n");
    add_item(({"bank","bay trees","thickets","thicket","slope"}), 
        "Dark-leaved bay trees form an impenetrable thicket west of "
            + "the slope.\n");
    add_cmd_item( ({ "thickets", "thicket", }), "enter", 
        "The thicket is impenetrable, that means you cannot enter it.\n");

    add_item( ({"stream"}),
        "The small stream leaves the lake spilling out over a stony lip " +
        "southeast of here.\n");
    add_item( ({ "ferns", "flower", "flowers", "herbs", "forest", "wood",
        "woods", "fern", "fern bed", }), BSN(
        "The fern forms a deep brown bed here. It grows high enough to " +
        "hide someone lying down from casual glances. Among the ferns, " +
        "herbs and flowers are growing. You recognize mints and " +
        "parsleys sprouting among the ferns."));
    add_item( ({"lake","basin","pool","water"}), BSN("The small lake "
        + "lies in the broken ruins of an ancient stone basin. A "
        + "small stream is feeding it to the east, and at the western "
        + "end the water spills out again over a stony lip."));

    set_up_herbs( ({ HERB_DIR + "chervil", HERB_DIR + "fennel",
		     HERB_DIR + "savory",  HERB_DIR + "basil",
		     HERB_DIR + "athelas", }),
		  ({ "forest", "ground", "field", "flowers", }), 3);

    reset_room();
}

public void
reset_room()
{
    ::reset_room();

    clone_npcs(Rabbit, NPC_DIR + "rabbit", 20.0 + 20.0 * rnd(),
	       ITH_DIR + "nforest");
}
